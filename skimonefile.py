#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep 14 11:01:46 2018

@author: Suyong Choi (Department of Physics, Korea University suyong@korea.ac.kr)

This script applies nanoaod processing to one file
"""

import sys
import cppyy
import ROOT
#from jobconfig import config, procflags
from importlib import import_module
from argparse import ArgumentParser

if __name__=='__main__':
    parser = ArgumentParser(usage="%prog inputfile outputfile jobconfmod")
    parser.add_argument("infile")
    parser.add_argument("outfile")
    parser.add_argument("jobconfmod")
    args = parser.parse_args()
    infile = args.infile
    outfile = args.outfile
    jobconfmod = args.jobconfmod

    # load job configuration python module and get bjects
    mod = import_module(jobconfmod)
    config = getattr(mod, 'config')
    procflags = getattr(mod, 'procflags')
    print("Job Configuration:", config)

    intreename = config['intreename']
    outtreename = config['outtreename']
    saveallbranches = procflags['saveallbranches']

    # load compiled C++ library into ROOT/python
    cppyy.load_reflection_info("libcorrectionlib.so")
    cppyy.load_reflection_info("libMathMore.so")
    cppyy.load_reflection_info("libnanoadrdframe.so")

    # ~~~~~~~~~~~~~~~~~~~~~~~~
    if infile.startswith('/store/'):
        infile = 'root://cmsxrootd.fnal.gov/' + infile
    # ~~~~~~~~~~~~~~~~~~~~~~~~

    t = ROOT.TChain(intreename)
    t.Add(infile)
    print(f"Inside process one file..!! Added file: {infile}")

    t.Print()
    nevents = t.GetEntries()
    print("-------------------------------------------------------------------")
    print("Total Number of Entries:")
    print(nevents)
    print("-------------------------------------------------------------------")

    aproc = ROOT.SkimEvents(t, outfile)

    # aproc = ROOT.TopSemiLeptAnalyzer(t, outfile)
    
    # setup JSONS for corrections
    #aproc.setupCorrections(config['goodjson'], config['pileupfname'], config['pileuptag']\
    #    , config['btvfname'], config['btvtype'], config['jercfname'], config['jerctag'], config['jercunctag'])
    # prepare for processing

    print("Setting up objects...")
    aproc.setupObjects()

    print("Setting up analysis...")
    aproc.setupAnalysis()

    print("Running the analysis...")
    aproc.run(saveallbranches, outtreename)

    print("Processing complete.")
