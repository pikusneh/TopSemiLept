#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep 14 11:01:46 2018
Modified Feb 26 2022

This script applies nanoaod processing to all the files in the input
 directory and its subdirectory recursively, copying directory structure to the outputdirectory

The main class that steers the processing is Nanoaodprocessor. For processing a single ROOT file,
it calls function_calling_PostProcessor, which executes processonefile.py as a separate process.
"""

import os
import re
import subprocess
import sys

from multiprocessing import Process
import cppyy
import ROOT


def function_calling_PostProcessor(outdir, rootfileshere, jobconfmod):
    for afile in rootfileshere:
        print(f"Processing file: {afile}")
        rootfname = re.split('\/', afile)[-1]
        withoutext = re.split('\.root', rootfname)[0]
        outfname = os.path.join(outdir, f"{withoutext}_analyzed.root")
        print(f"Output file will be: {outfname}")
        subprocess.run(["./processonefile.py", afile, outfname, jobconfmod])
    print("Finished processing files.")
    pass


class Nanoaodprocessor:
    def __init__(self, indir, outdir, jobconfmod, procflags, config):
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
        print(f"Initialization: year={self.year}, datatype={self.datatype}, indir={self.indir}, outdir={self.outdir}")

        # check whether input directory exists
        if not os.path.exists(self.indir):
            print(f'Path {indir} does not exist. Exiting.')
            exit(1)
        pass

    def process(self):
        print(f"Processing input directory: {self.indir}")
        self._processROOTfiles(self.indir, self.outdir)
        pass

    def _processROOTfiles(self, inputdirectory, outputdirectory):
        flist = [inputdirectory] if os.path.isfile(inputdirectory) else os.listdir(inputdirectory)
        print(f"Files in directory {inputdirectory}: {flist}")
        rootfileshere = []
        subdirs = []
        outsubdirs = []

        if not os.path.exists(outputdirectory):
            os.mkdir(outputdirectory)

        counter = 0
        for fname in flist:
            fullname = fname if os.path.isfile(inputdirectory) else os.path.join(inputdirectory, fname)
            if re.match(r'.*\.root', fname) and os.path.isfile(fullname):
                counter += 1
                if counter <= self.nrootfiles and self.nrootfiles != 0:
                    rootfileshere.append(fullname)
                elif self.nrootfiles == 0:
                    rootfileshere.append(fullname)
            elif os.path.isdir(fullname):
                subdirs.append(fullname)
                outsubdirs.append(os.path.join(outputdirectory, fname))

        print(f"ROOT files to process: {rootfileshere}")

        if len(rootfileshere) > 0:
            print("Running processing")
            if self.skipold:
                oflist = os.listdir(outputdirectory)
                filteredoflist = []
                for fname in oflist:
                    fullname = os.path.join(outputdirectory, fname)
                    if re.match(r'.*\.root', fname) and os.path.isfile(fullname):
                        withoutext = re.split(r"\.root", fname)[0]
                        wihoutskimtext = re.split(r"\_analyzed", withoutext)[0]
                        filteredoflist.append(wihoutskimtext)
                print(f"Root files in output directory: {filteredoflist}")
                filterediflist = []
                for ifname in rootfileshere:
                    rootfname = re.split(r'\/', ifname)[-1]
                    withoutext = re.split(r'\.root', rootfname)[0]
                    if withoutext not in filteredoflist:
                        print(f"{withoutext} not yet in output dir")
                        filterediflist.append(ifname)
                    else:
                        print(f"{withoutext} in output dir")

                rootfileshere = filterediflist

            if self.split > 1:
                njobs = self.split
                nfileperjob = len(rootfileshere) / njobs
                print("Running multiprocessing")

                if len(rootfileshere) < self.split:
                    njobs = len(rootfileshere)
                    nfileperjob = 1

                print("Splitting files for multiprocessing")

                ap = []
                for i in range(njobs):
                    if i < njobs - 1:
                        filesforjob = rootfileshere[int(i * nfileperjob):int((i + 1) * nfileperjob)]
                    else:
                        filesforjob = rootfileshere[int(i * nfileperjob):]
                    p = Process(target=function_calling_PostProcessor, args=(outputdirectory, filesforjob, self.jobconfmod))
                    p.start()
                    ap.append(p)
                for proc in ap:
                    proc.join()
            else:
                for afile in rootfileshere:
                    print(f"Processing file: {afile}")
                    rootfname = re.split(r'\/', afile)[-1]
                    withoutext = re.split(r'\.root', rootfname)[0]
                    outfname = os.path.join(outputdirectory, f"{withoutext}_analyzed.root")
                    print(f"Output file will be: {outfname}")
                    subprocess.run(["./processonefile.py", afile, outfname, self.jobconfmod])

        if self.recursive:
            for indir, outdir in zip(subdirs, outsubdirs):
                self._processROOTfiles(indir, outdir)


def Nanoaodprocessor_singledir(indir, outputroot, procflags, config):
    if not re.match(r'.*\.root', outputroot):
        print("Output file should be a root file! Quitting.")
        exit(-1)

    fullnamelist = []
    rootfilestoprocess = []
    print(f"COLLECT root files in: {indir}")

    if os.path.isfile(indir):
        fullnamelist.append(indir)
    elif not procflags['recursive']:
        flist = os.listdir(indir)
        for fname in flist:
            fullname = os.path.join(indir, fname)
            fullnamelist.append(fullname)
    else:
        for root, dirs, flist in os.walk(indir):
            for fname in flist:
                fullname = os.path.join(root, fname)
                fullnamelist.append(fullname)
    counter = 0
    for fname in fullnamelist:
        if re.match(r'.*\.root', fname) and os.path.isfile(fname):
            counter += 1
            if counter <= procflags['nrootfiles'] and procflags['nrootfiles'] != 0:
                rootfilestoprocess.append(fname)
            elif procflags['nrootfiles'] == 0:
                rootfilestoprocess.append(fname)

    print("FILES to PROCESS")
    print(rootfilestoprocess)

    intreename = config['intreename']
    outtreename = config['outtreename']
    saveallbranches = procflags['saveallbranches']
    
    # Create TChain and add files
    t = ROOT.TChain(intreename)
    for afile in rootfilestoprocess:
        print(f"Adding file to TChain: {afile}")
        t.Add(afile)

    # Print the TChain to verify it's correctly set up
    t.Print()

    nevents = t.GetEntries()
    print("-------------------------------------------------------------------")
    print("Total Number of Entries:")
    print(nevents)
    print("-------------------------------------------------------------------")

    #aproc = ROOT.FourtopAnalyzer(t, outputroot)
    aproc = ROOT.TopSemiLeptAnalyzer(t, outputroot)
    aproc.setParams(config['year'], config['runtype'], config['datatype'])

    skipcorrections = False
    if not skipcorrections:
        print("correction step is on play")
        aproc.setupCorrections(config['goodjson'], config['pileupfname'], config['pileuptag'], config['btvfname'], config['btvtype'], config['muon_fname'], config['muontype'], config['jercfname'], config['jerctag'], config['jercunctag'])
    else:
        print("Skipping corrections step")

    print("Starting setupanalysis")
    sys.stdout.flush()  # to force printout in the right order
    aproc.setupObjects()
    aproc.setupAnalysis()
    aproc.run(saveallbranches, outtreename)

    print("Processing complete.")
    pass


if __name__ == '__main__':
    from importlib import import_module
    from argparse import ArgumentParser

    parser = ArgumentParser(usage="%prog inputDir outputDir jobconfmod")
    parser.add_argument("indir")
    parser.add_argument("outdir")
    parser.add_argument("jobconfmod")
    args = parser.parse_args()

    indir = args.indir
    outdir = args.outdir
    jobconfmod = args.jobconfmod

    if not os.path.exists(indir):
        print(f'Path {indir} does not exist. Stopping')
        exit(1)

    cppyy.load_reflection_info("libcorrectionlib.so")
    cppyy.load_reflection_info("libMathMore.so")
    cppyy.load_reflection_info("libnanoadrdframe.so")

    mod = import_module(jobconfmod)
    procflags = getattr(mod, 'procflags')
    config = getattr(mod, 'config')

    if not procflags['allinone']:
        print("not allinone")
        n = Nanoaodprocessor(indir, outdir, jobconfmod, procflags, config)
        n.process()
    else:
        print("allinone")
        Nanoaodprocessor_singledir(indir, outdir, procflags, config)
