#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep 14 11:01:46 2018

This script applies nanoaod processing to one file.
"""

import sys
import cppyy
import ROOT
from importlib import import_module
from argparse import ArgumentParser

if __name__ == '__main__':
    # Correcting the usage string format
    parser = ArgumentParser(usage="%(prog)s infile outfile jobconfmod samplename")
    parser.add_argument("infile", help="Input ROOT file")
    parser.add_argument("outfile", help="Output ROOT file")
    parser.add_argument("jobconfmod", help="Job configuration module")
    parser.add_argument("samplename", help="Name of the sample being processed")
    args = parser.parse_args()

    infile = args.infile
    outfile = args.outfile
    jobconfmod = args.jobconfmod
    samplename = args.samplename

    # load job configuration python module and get objects
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

    # Ensure infile is fully qualified if it is a remote file
    if infile.startswith('/store/'):
        infile = 'root://cmsxrootd.fnal.gov/' + infile

    t = ROOT.TChain(intreename)
    t.Add(infile)
    print(f"Inside process one file..!! Added file: {infile}")

    # Print the TChain to verify it's correctly set up
    # t.Print()

    nevents = t.GetEntries()
    print("-------------------------------------------------------------------")
    print("Total Number of Entries:")
    print(nevents)
    print("-------------------------------------------------------------------")

    # Initialize the analyzer
    aproc = ROOT.TopSemiLeptAnalyzer(t, outfile, samplename)
    aproc.setParams(config['year'], config['runtype'], config['datatype'])

    print("Setting up corrections...")
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
        config['photon_fname'],
        config['photon_id_type'],
        config['jercfname'],
        config['jerctag'],
        config['jercunctag']
    )

    sys.stdout.flush()  # to force printout in right order

    # Prepare for processing
    print("Setting up objects...")
    aproc.setupObjects()

    print("Setting up analysis...")
    aproc.setupAnalysis()

    print("Running the analysis...")
    aproc.run(saveallbranches, outtreename)

    print("Processing complete.")
