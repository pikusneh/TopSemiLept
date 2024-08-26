#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
from importlib import import_module

# loop over the directories and submit background jobs
def submit(jobconfmod):

    # get input directory, outputdirectory, stderrout file from the job configuration python module
    mod = import_module(jobconfmod)
    nanoaod_inputdir_outputdir_pairs = getattr(mod, 'nanoaod_inputdir_outputdir_pairs')
    sample_names = getattr(mod, 'sample_names')

    # job configuation module name is to be passed to the skim nanoaod main 
    for i, (indir, outdir, outfile) in enumerate(nanoaod_inputdir_outputdir_pairs):
        sample_name = sample_names[i]
        command = f'./processnanoaod.py {indir} {outdir} {jobconfmod} {sample_name} > {outfile} 2>&1 &'
        print(f"Submitting job with command: {command}")
        os.system(command)

    pass



if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser(usage="%prog jobconfigmodule", description='Submits skim jobs in background where the job configuration python module name should be passed')
    parser.add_argument("jobconfmod")
    args = parser.parse_args()

    jobconfmod_fname = args.jobconfmod
    jobconfmod = jobconfmod_fname.replace('.py', '')

    submit(jobconfmod)

    pass