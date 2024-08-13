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
from argparse import ArgumentParser
from importlib import import_module

from XRootD import client


def function_calling_PostProcessor(sample_name, outdir, rootfileshere, jobconfmod):
    for afile in rootfileshere:
        print(f"Processing file: {afile}")
        rootfname = re.split('\/', afile)[-1]
        withoutext = re.split('\.root', rootfname)[0]
        outfname = os.path.join(outdir, f"{withoutext}_analyzed.root")
        print(f"Output file will be: {outfname}")
        subprocess.run(["./processonefile.py", afile, outfname, jobconfmod, sample_name])
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

        #  # check whether input directory exists
        # if not self.indir.startswith('root://') and not os.path.exists(self.indir):
        #     print(f'Path {self.indir} does not exist. Exiting.')
        #     exit(1)
        # pass

    def process(self):
        print(f"Processing input directory: {self.indir}")
        self._processROOTfiles(self.indir, self.outdir)
        pass

    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    def _list_root_files_in_directory(self,path):
        root_files = []
        print(f"dir 2 search :{path}")
        # Use TSystem to check if the path is a directory
        system = ROOT.gSystem
        if system.IsDirectory(path):
            directory = system.OpenDirectory(path)
            if not directory:
                print(f"Cannot open directory {path}")
                return root_files
            
            # List files in the directory
            while True:
                entry = system.GetDirEntry(directory)
                if not entry:
                    break
                # Check if the entry is a ROOT file
                if entry.endswith(".root"):
                    root_files.append(entry)
            
            system.FreeDirectory(directory)
        else:
            print(f"{path} is not a directory.")
        print(f"root files found in root dir {path}: {root_files}")
        return root_files
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    def _processROOTfiles(self, inputdirectory, outputdirectory):
        # check input path starts with root:// and doesnt end with .root
        if inputdirectory.startswith('root://') and not re.match(r'.*\.root', fname):
            flist = self._list_root_files_in_directory(inputdirectory)
        else:
            flist = [inputdirectory] if os.path.isfile(inputdirectory) else os.listdir(inputdirectory)
        # if inputdirectory.startswith('root://'):
        #     server = inputdirectory.split('//')[1].split('/')[0]
        #     path = inputdirectory.split(server)[1]
        #     flist = subprocess.check_output(["xrdfs", server, "ls", path]).decode().splitlines()
        #     flist = [f.strip() for f in flist]
        # else:
        #     flist = [inputdirectory] if os.path.isfile(inputdirectory) else os.listdir(inputdirectory)
        
        print(f"Files in directory {inputdirectory}: {flist}")
        rootfileshere = []
        subdirs = []
        outsubdirs = []

        if not os.path.exists(outputdirectory):
            os.mkdir(outputdirectory)

        counter = 0
        for fname in flist:
            fullname = fname if inputdirectory.startswith('root://') else os.path.join(inputdirectory, fname)
            # fullname = f"{inputdirectory}/{fname}" if inputdirectory.startswith('root://') else os.path.join(inputdirectory, fname)
            # if re.match(r'.*\.root', fname) and os.path.isfile(fullname):
            if re.match(r'.*\.root', fname) and (inputdirectory.startswith('root://') or os.path.isfile(fullname)):
                counter += 1
                if counter <= self.nrootfiles and self.nrootfiles != 0:
                    rootfileshere.append(fullname)
                elif self.nrootfiles == 0:
                    rootfileshere.append(fullname)
            elif os.path.isdir(fullname) and not inputdirectory.startswith('root://'):
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

        if self.recursive and not inputdirectory.startswith('root://'):
            for indir, outdir in zip(subdirs, outsubdirs):
                self._processROOTfiles(indir, outdir)

def get_root_file_paths(indir, xrootd_prefix="root://cmsxrootd.fnal.gov/"):
    """
    Function to retrieve ROOT file paths using dasgoclient.
    """
    # Run dasgoclient command to get the list of files
    dataset_query = f"file dataset={indir}"
    command = f"dasgoclient --query='{dataset_query}'"
    try:
        output = subprocess.check_output(command, shell=True, text=True)
    except subprocess.CalledProcessError as e:
        print(f"Error running dasgoclient: {e.output}")
        return []

    # Process the output and prepend the xrootd prefix
    files = output.strip().split('\n')
    root_files = [xrootd_prefix + f for f in files]

    return root_files


def list_root_files_in_directory(path, nFiles):
    """
    Function to list ROOT files in a directory using ROOT's TSystem.
    """
    root_files = []
    seen_files = set()
    print(f"Directory to search: {path} for number of files: {nFiles}")

    # Use TSystem to check if the path is a directory
    system = ROOT.gSystem
    directory = system.OpenDirectory(path)
    
    if not directory:
        print(f"Cannot open directory {path}")
        return root_files
    
    try:
        file_count = 0
        while True:
            entry = system.GetDirEntry(directory)
            if not entry:
                break
            
            # Skip special entries and duplicates
            if entry in ['.', '..']:
                continue
            
            # Construct full path correctly
            full_path = os.path.join(path, entry)
            
            # Check if the entry is a ROOT file
            if entry.endswith(".root") and entry not in seen_files:
                root_files.append(full_path)
                seen_files.add(entry)  # Add to the set of seen files
                file_count += 1
                print(f"Added file: {entry}")  # Debugging log
            
            if file_count >= nFiles:
                break
    finally:
        # Always free directory resource
        system.FreeDirectory(directory)

    print(f"ROOT files found in directory {path}: {root_files}")
    return root_files

     # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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


def Nanoaodprocessor_singledir(sample_name,indir, outputroot, procflags, config):

    if not re.match(r'.*\.root$', outputroot):
        print("Output file should be a root file! Quitting.")
        exit(-1)

    fullnamelist = []
    rootfilestoprocess = []
    print(f"COLLECT root files in: {indir}")

    if indir.startswith('/'):
        print("Detected a dataset path, querying DAS using dasgoclient")
        fullnamelist = get_root_file_paths(indir)
        # print("Files found in dataset:", fullnamelist) //debug
    else:
        print(f"Invalid path: {indir}. Exiting.")
        exit(-1)
    
        # Limit the number of files to process if specified
    if procflags['nrootfiles'] > 0:
        rootfilestoprocess = fullnamelist[:procflags['nrootfiles']]
    else:
        rootfilestoprocess = fullnamelist

    intreename = config['intreename']
    outtreename = config['outtreename']
    saveallbranches = procflags['saveallbranches']

    # Create TChain and add files
    t = ROOT.TChain(intreename)
    for afile in rootfilestoprocess:
        print(f"Adding file to TChain: {afile}")
        t.Add(afile)

    # Print the TChain to verify it's correctly set up
    print(f"PRINT")
    # tree = t.Print()

    nevents = t.GetEntries()
    print("-------------------------------------------------------------------")
    print("Total Number of Entries:")
    print(nevents)
    print("-------------------------------------------------------------------")

    aproc= ROOT.TopSemiLeptAnalyzer(t, outputroot, sample_name)
    aproc.setParams(config['year'], config['runtype'], config['datatype'])

    aproc.setupCorrections(
            config['goodjson'],
            config['pileupfname'],
            config['pileuptag'],
            config['btvfname'],
            config['btvtype'],
            config['muon_roch_fname'],
            config['muon_fname'],
            config['muon_HLT_type'],
            config['muon_RECO_type'],
            config['muon_ID_type'],
            config['muon_ISO_type'],
            config['electron_fname'],
            config['electron_reco_type'],
            config['electron_id_type'],
            config['jercfname'],
            config['jerctag'],
            config['jercunctag']
        )
        
    # else:
    #     print("Skipping corrections step")

    print("Starting setupanalysis")
    sys.stdout.flush()  # to force printout in the right order
    aproc.setupObjects()
    aproc.setupAnalysis()
    aproc.run(saveallbranches, outtreename)

    print("Processing complete.")
    # pass

if __name__ == '__main__':

    from importlib import import_module
    from argparse import ArgumentParser
    
    # parser = ArgumentParser(usage="%prog sample_list_file jobconfmod")
    parser = ArgumentParser(description="Process NanoAOD files.")
    parser.add_argument("indir", help="Input directory, dataset path, or file path")
    parser.add_argument("outdir", help="Output directory or ROOT file")
    parser.add_argument("jobconfmod", help="Job configuration module")
    parser.add_argument("sample_name", help="Name of the sample being processed")
    args = parser.parse_args()

    indir = args.indir
    outdir = args.outdir
    jobconfmod = args.jobconfmod
    sample_name = args.sample_name


    print(f"indir in main: {indir}")

    if is_valid_das_path(indir):
        # This is a DAS dataset path
        print(f'Processing as a DAS dataset path: {indir}')
    else:
        # None of the above, invalid input
        print(f'Path {indir} is not a valid local path, remote path, or DAS dataset. Stopping.')
        exit(1)


    cppyy.load_reflection_info("libcorrectionlib.so")
    cppyy.load_reflection_info("libMathMore.so")
    cppyy.load_reflection_info("libnanoadrdframe.so")

    mod = import_module(jobconfmod)
    procflags = getattr(mod, 'procflags')
    config = getattr(mod, 'config')

    # print(f"hellooooo")

    print(f'Processing sample {sample_name} as a DAS dataset path: {indir}')
    Nanoaodprocessor_singledir(sample_name, indir, outdir, procflags, config)

