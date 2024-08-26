#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import re
import subprocess
import sys
from multiprocessing import Process
from importlib import import_module
from argparse import ArgumentParser
import ROOT
import cppyy

from XRootD import client

def get_root_file_paths(indir, xrootd_prefix="root://cmsxrootd.fnal.gov/"):
    """
    Function to retrieve ROOT file paths using dasgoclient.
    """
    dataset_query = f"file dataset={indir}"
    command = f"dasgoclient --query='{dataset_query}'"
    try:
        output = subprocess.check_output(command, shell=True, text=True)
    except subprocess.CalledProcessError as e:
        print(f"Error running dasgoclient: {e.output}")
        return []

    files = output.strip().split('\n')
    root_files = [xrootd_prefix + f for f in files]

    return root_files

def is_valid_das_path(indir):
    """
    Check if the indir is a valid DAS path by querying dasgoclient.
    """
    command = f"dasgoclient --query='dataset={indir}'"
    try:
        output = subprocess.check_output(command, shell=True, text=True)
        return bool(output.strip())
    except subprocess.CalledProcessError:
        return False

def function_calling_PostProcessor(outdir, rootfileshere, jobconfmod, samplename):
    for afile in rootfileshere:
        rootfname = os.path.basename(afile)
        withoutext = os.path.splitext(rootfname)[0]
        outfname = os.path.join(outdir, f"{withoutext}_analyzed.root")
        subprocess.run(["./skimonefile.py", afile, outfname, jobconfmod, samplename])

class Nanoaodprocessor:
    def __init__(self, indir, outdir, jobconfmod, procflags, config, samplename):
        self.outdir = outdir
        self.indir = indir
        self.jobconfmod = jobconfmod
        self.split = procflags['split']
        self.skipold = procflags['skipold']
        self.recursive = procflags['recursive']
        self.saveallbranches = procflags['saveallbranches']
        self.nrootfiles = procflags['nrootfiles']
        self.year = config['year']
        self.runtype = config['runtype']
        self.datatype = config['datatype']
        self.samplename = samplename

        if is_valid_das_path(indir):
            self.rootfiles = get_root_file_paths(indir)
        else:
            self.rootfiles = self._get_local_root_files(indir)

        if not self.rootfiles:
            print(f"No ROOT files found in {indir}")
            exit(1)

        print(f"Total ROOT files: {len(self.rootfiles)}")

        for rootfile in self.rootfiles:
            print(rootfile)

    def _get_local_root_files(self, inputdirectory):
        rootfiles = [os.path.join(inputdirectory, fname)
                     for fname in os.listdir(inputdirectory)
                     if fname.endswith('.root') and os.path.isfile(os.path.join(inputdirectory, fname))]
        return rootfiles

    def process(self):
        self._processROOTfiles(self.rootfiles, self.outdir)

    def _processROOTfiles(self, rootfiles, outputdirectory):
        if not os.path.exists(outputdirectory):
            os.mkdir(outputdirectory)

        if self.skipold:
            rootfiles = self._filter_existing_files(rootfiles, outputdirectory)

        if self.split == 'Max':
            njobs = len(rootfiles)
            nfileperjob = 1
        else:
            njobs = self.split
            nfileperjob = len(rootfiles) * 1.0 / njobs
            if len(rootfiles) < njobs:
                njobs = len(rootfiles)
                nfileperjob = 1

            print(f"Splitting {len(rootfiles)} files into {njobs} jobs.")

        ap = []
        for i in range(njobs):
            filesforjob = rootfiles[int(i * nfileperjob):int((i + 1) * nfileperjob)] if i < njobs - 1 else rootfiles[int(i * nfileperjob):]
            print(f"Job {i+1} will process {len(filesforjob)} files.")
            p = Process(target=function_calling_PostProcessor, args=(outputdirectory, filesforjob, self.jobconfmod, self.samplename))
            p.start()
            ap.append(p)
        for proc in ap:
            proc.join()

    def _filter_existing_files(self, rootfiles, outputdirectory):
        oflist = os.listdir(outputdirectory)
        processed_files = {re.split("\_analyzed", os.path.splitext(fname)[0])[0] for fname in oflist if fname.endswith('.root')}
        return [fname for fname in rootfiles if os.path.splitext(os.path.basename(fname))[0] not in processed_files]

class Nanoaodprocessor_singledir:
    def __init__(self, indir, outputroot, procflags, config, samplename):
        self.outputroot = outputroot
        self.indir = indir
        self.procflags = procflags
        self.config = config
        self.samplename = samplename

        if is_valid_das_path(indir):
            self.rootfiles = get_root_file_paths(indir)
        else:
            self.rootfiles = self._get_local_root_files(indir)

        if not self.rootfiles:
            print(f"No ROOT files found in {indir}")
            exit(1)

    def _get_local_root_files(self, inputdirectory):
        rootfiles = [os.path.join(inputdirectory, fname)
                     for fname in os.listdir(inputdirectory)
                     if fname.endswith('.root') and os.path.isfile(os.path.join(inputdirectory, fname))]
        return rootfiles

    def process(self):
        self._processROOTfiles(self.rootfiles, self.outputroot)

    def _processROOTfiles(self, rootfiles, outputdir):
        if self.procflags['split'] == 'Max':
            njobs = len(rootfiles)
            nfileperjob = 1
        else:
            njobs = self.procflags['split']
            nfileperjob = len(rootfiles) * 1.0 / njobs
            if len(rootfiles) < njobs:
                njobs = len(rootfiles)
                nfileperjob = 1

        print(f"Splitting {len(rootfiles)} files into {njobs} jobs.")

        ap = []
        for i in range(njobs):
            filesforjob = rootfiles[int(i * nfileperjob):int((i + 1) * nfileperjob)] if i < njobs - 1 else rootfiles[int(i * nfileperjob):]
            print(f"Job {i+1} will process {len(filesforjob)} files.")
            job_output_file = os.path.join(outputdir, f"{self.samplename}_job{i+1}.root")
            p = Process(target=self._process_files_in_job, args=(filesforjob, job_output_file))
            p.start()
            ap.append(p)

        for proc in ap:
            proc.join()

    def _process_files_in_job(self, filesforjob, outputroot):
        intreename = self.config['intreename']
        outtreename = self.config['outtreename']
        saveallbranches = self.procflags['saveallbranches']

        t = ROOT.TChain(intreename)
        for afile in filesforjob:
            t.Add(afile)
        nevents = t.GetEntries()
        print("-------------------------------------------------------------------")
        print(f"Total Number of Entries: {nevents}")
        print("-------------------------------------------------------------------")

        aproc = ROOT.TopSemiLeptAnalyzer(t, outputroot, self.samplename)
        aproc.setParams(self.config['year'], self.config['runtype'], self.config['datatype'])
        skipcorrections = True
        if not skipcorrections:
            aproc.setupCorrections(config['goodjson'], config['pileupfname'], config['pileuptag']\
                , config['btvfname'], config['btvtype'], config['jercfname'], config['jerctag'], config['jercunctag'])
            aproc.setupObjects()
        else:
            print("Skipping corrections step")
        aproc.setupAnalysis()
        aproc.run(saveallbranches, outtreename)


        sys.stdout.flush()  # to force printout in the right order

        print("Setting up objects...")
        aproc.setupObjects()

        print("Setting up analysis...")
        aproc.setupAnalysis()

        print("Running the analysis...")
        aproc.run(saveallbranches, outtreename)

        print(f"Processing complete for job {outputroot}.")

if __name__ == '__main__':
    parser = ArgumentParser(usage="%(prog)s indir outdir jobconfmod samplename")
    parser.add_argument("indir", help="Input directory or DAS dataset path")
    parser.add_argument("outdir", help="Output directory or output ROOT file")
    parser.add_argument("jobconfmod", help="Job configuration module (Python file)")
    parser.add_argument("samplename", help="Name of the sample being processed")

    args = parser.parse_args()

    indir = args.indir
    outdir = args.outdir
    jobconfmod = args.jobconfmod
    samplename = args.samplename

    cppyy.load_reflection_info("libcorrectionlib.so")
    cppyy.load_reflection_info("libMathMore.so")
    cppyy.load_reflection_info("libnanoadrdframe.so")

    mod = import_module(jobconfmod)
    procflags = getattr(mod, 'procflags')
    config = getattr(mod, 'config')

    if not procflags['allinone']:
        print("Processing with Nanoaodprocessor")
        n = Nanoaodprocessor(indir, outdir, jobconfmod, procflags, config, samplename)
        n.process()
    else:
        print("Processing with Nanoaodprocessor_singledir")
        Nanoaodprocessor_singledir(indir, outdir, procflags, config, samplename).process()
