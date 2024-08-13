#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep 14 11:01:46 2018

@author: Suyong Choi (Department of Physics, Korea University suyong@korea.ac.kr)

This script applies nanoaod processing to all the files in the input
 directory and its subdirectory recursively, copying directory structure to the outputdirectory

"""
import os
import re
import subprocess
from multiprocessing import Process
import cppyy
import ROOT
from argparse import ArgumentParser
from importlib import import_module


def function_calling_PostProcessor(outdir, rootfileshere, jobconfmod):
    for afile in rootfileshere:
        print(f"Processing file: {afile}")
        rootfname = re.split('\/', afile)[-1]
        withoutext = re.split('\.root', rootfname)[0]
        outfname = os.path.join(outdir, f"{withoutext}_analyzed.root")
        # outfname = outdir + '/' + withoutext + '_analyzed.root'
        subprocess.run(["./skimonefile.py", afile, outfname, jobconfmod])
    pass


# def function_calling_PostProcessor(outdir, rootfileshere, jobconfmod):
#     for afile in rootfileshere:
#         rootfname = os.path.basename(afile)
#         withoutext = os.path.splitext(rootfname)[0]
#         outfname = os.path.join(outdir, f"{withoutext}_analyzed.root")
#         subprocess.run(["./skimonefile.py", afile, outfname, jobconfmod])
#     pass

class Nanoaodprocessor:
    def __init__(self, indir, outdir, jobconfmod, procflags, config):
        self.outdir = outdir
        self.indir = indir
        self.jobconfmod = jobconfmod

        self.split = procflags['split']
        self.skipold = procflags['skipold']
        self.recursive = procflags['recursive']
        self.saveallbranches = procflags['saveallbranches']
        
        # check whether input directory exists
        if not os.path.exists(self.indir):
            print ('Path '+indir+' does not exist')
            exit(1)
        pass
        # if not os.path.exists(self.indir) and not self.indir.startswith('root://'):
        #     print(f'Path {self.indir} does not exist')
        #     exit(1)
        # pass

    def process(self):
        self._processROOTfiles(self.indir, self.outdir)
        pass


    # def _processROOTfiles(self, inputdirectory, outputdirectory):
    #     # list currect directory
    #     flist = os.listdir(inputdirectory) 
    #     print(flist)
    #     rootfileshere = []
    #     subdirs = []
    #     outsubdirs = []
    #     # create output directory if it doesn't already exist
    #     if not os.path.exists(outputdirectory):
    #         os.mkdir(outputdirectory)
    #     # loop through the list
    #     # pick root files but not those that match  _analyzed.root 
    #     for fname in flist:
    #         fullname = os.path.join(inputdirectory, fname)
    #         if re.match('.*\.root', fname) and not re.match('.*_analyzed\.root', fname) and os.path.isfile(fullname): # if it has .root file extension
    #             rootfileshere.append(fullname) 
    #         elif os.path.isdir(fullname):  # if it's a directory name
    #             subdirs.append(fullname)
    #             outsubdirs.append(outputdirectory+'/'+fname)
        
    #     print("files found in directory "+inputdirectory)
    #     print(rootfileshere)
        
    #     # run
    #     if len(rootfileshere)>0:
    #         if self.skipold: # if processed file exists, then skip, otherwise make a list of unprocessed files
    #             oflist = os.listdir(outputdirectory)
    #             filteredoflist = []
    #             for fname in oflist :
    #                 fullname = os.path.join(outputdirectory, fname)
    #                 if re.match('.*\.root', fname) and os.path.isfile(fullname): # if it has .root file extension:
    #                     withoutext = re.split("\.root", fname)[0]
    #                     wihoutskimtext = re.split("\_analyzed", withoutext)[0]
    #                     filteredoflist.append(wihoutskimtext)
    #             print('root files in output directory')
    #             print(filteredoflist)
    #             filterediflist = []
    #             for ifname in rootfileshere:
    #                 rootfname = re.split('\/', ifname)[-1]
    #                 withoutext = re.split('\.root', rootfname)[0]
    #                 if withoutext not in filteredoflist:
    #                     print(withoutext+' not yet in output dir')
    #                     filterediflist.append(ifname)
    #                 else:
    #                     print(withoutext+' in output dir')
                         
    #             rootfileshere = filterediflist

    #         if self.split>1: # use multiprocessing
    #             njobs = self.split
    #             nfileperjob = len(rootfileshere) *1.0 / njobs

    #             # if number of files is less than the number of splits desired
    #             if len(rootfileshere) < self.split:
    #                 njobs = len(rootfileshere)
    #                 nfileperjob = 1

    #             print ("splitting files")
                
    #             ap = []
    #             for i in range(njobs):
    #                 if i<njobs-1:
    #                     filesforjob = rootfileshere[int(i*nfileperjob):int((i+1)*nfileperjob)]
    #                 else:
    #                     filesforjob = rootfileshere[int(i*nfileperjob):]
    #                 p = Process(target=function_calling_PostProcessor, args=(outputdirectory, filesforjob, self.jobconfmod)) # positional arguments go into kwargs
    #                 p.start()
    #                 ap.append(p)
    #             for proc in ap:
    #                 proc.join()
    #         else: # no multiprocessing
    #             #function_calling_PostProcessor(outputdirectory, rootfileshere, self.json, self.isdata)
    #             aproc = None
    #             for afile in rootfileshere:
    #                 rootfname = re.split('\/', afile)[-1]
    #                 withoutext = re.split('\.root', rootfname)[0]
    #                 outfname = outputdirectory +'/'+ withoutext + '_analyzed.root'
    #                 subprocess.run(["./skimonefile.py", afile, outfname, self.jobconfmod])

    #     # if there are subdirectories recursively call
    #     if self.recursive:
    #         for indir, outdir in zip(subdirs, outsubdirs):
    #             self._processROOTfiles(indir, outdir)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def Nanoaodprocessor_singledir(indir, outputroot, procflags, config):
    """Runs nanoaod analyzer over ROOT files in indir 
    and run outputs into a signel ROOT file.
    
    Arguments:
        outputroot {string} -- [description]
        indir {string} -- [description]
        json {string} -- [description]
    """

    if not re.match(r'.*\.root$', outputroot):
        print("Output file should be a root file! Quitting")
        exit(-1)

    fullnamelist =[]
    rootfilestoprocess = []
    print(f"COLLECT root files in: {indir}")

    if indir.startswith('/'):
        print("Detected a dataset path, querying DAS using dasgoclient")
        fullnamelist = get_root_file_paths(indir)
        print("Files found in dataset:", fullnamelist)
        rootfilestoprocess = fullnamelist

    # if not procflags['recursive']:
    #     flist = os.listdir(indir)
    #     for fname in flist:
    #         fullname = os.path.join(indir, fname)
    #         fullnamelist.append(fullname)
    # else: # os.walk lists directories recursively (here, we will not follow symlink)
    #     for root, dirs, flist in os.walk(indir):
    #         for fname in flist:
    #             fullname = os.path.join(root, fname)
    #             fullnamelist.append(fullname)

    # for  fname in fullnamelist:            
    #     if re.match('.*\.root', fname) and os.path.isfile(fname): # if it has .root file extension
    #         rootfilestoprocess.append(fname)

    # print("files to process")
    # print(rootfilestoprocess)

    intreename = config['intreename']
    outtreename = config['outtreename']
    saveallbranches = procflags['saveallbranches']

    t = ROOT.TChain(intreename)
    for afile in rootfilestoprocess:
        print(f"Adding file to TChain: {afile}")
        t.Add(afile)

    aproc = ROOT.SkimEvents(t, outputroot)
    # aproc = ROOT.TopSemiLeptAnalyzer(t, outputroot)
    #aproc.setupCorrections(config['goodjson'], config['pileupfname'], config['pileuptag']\
    #    , config['btvfname'], config['btvtype'], config['jercfname'], config['jerctag'], config['jercunctag'])
    # aproc.setupObjects()
    # aproc.setupAnalysis()
    aproc.defineCuts();
    aproc.defineMoreVars();
    aproc.bookHists();
    aproc.run(saveallbranches, outtreename)
    pass

if __name__=='__main__':
    from importlib import import_module
    from argparse import ArgumentParser
    # inputDir and lower directories contain input NanoAOD files
    # outputDir is where the outputs will be created
    parser = ArgumentParser(usage="%prog inputDir outputDir jobconfmod")
    parser.add_argument("indir")
    parser.add_argument("outdir")
    parser.add_argument("jobconfmod")
    args = parser.parse_args()

    indir = args.indir
    outdir = args.outdir
    jobconfmod = args.jobconfmod

    if is_valid_das_path(indir):
        # This is a DAS dataset path
        print(f'Processing as a DAS dataset path: {indir}')
    else:
        # None of the above, invalid input
        print(f'Path {indir} is not a valid local path, remote path, or DAS dataset. Stopping.')
        exit(1)

    # check whether input directory exists
    # if not os.path.exists(indir):
    #     print ('Path '+indir+' does not exist. Stopping')
    #     exit(1)
# add this condition later if want to run with local files instead of DAS files
    # if not os.path.exists(indir) and not indir.startswith('root://'):
    #     print(f'Path {indir} does not exist. Stopping')
    #     exit(1)

    # load compiled C++ library into ROOT/python
    cppyy.load_library("libcorrectionlib.so")
    cppyy.load_library("libMathMore.so")
    cppyy.load_library("libnanoadrdframe.so")

    # read in configurations from job configuration python module
    mod = import_module(jobconfmod)
    procflags = getattr(mod, 'procflags')
    config = getattr(mod, 'config')

    if not procflags['allinone']:
        print("not allinone")
        # n=Nanoaodprocessor(indir, outdir, jobconfmod, procflags, config)
        # n.process()
    else:
        print("allinone")
        Nanoaodprocessor_singledir (indir, outdir, procflags, config) # although it says outdir, it should really be a output ROOT file name
