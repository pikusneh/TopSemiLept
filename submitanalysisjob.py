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

# def submit(jobconfmod):

#     # Get input directory, output directory, stderrout file from the job configuration python module
#     mod = import_module(jobconfmod)

#     nanoaod_inputdir_outputdir_pairs = getattr(mod, 'nanoaod_inputdir_outputdir_pairs')
#     sample_names = getattr(mod, 'sample_names')
#     procflags = getattr(mod, 'procflags')

#     # Job configuration module name is to be passed to the skim nanoaod main 
#     for i, (indir, outdir_base, stderrout_file) in enumerate(nanoaod_inputdir_outputdir_pairs):
#         sample_name = sample_names[i]
        
#         # Ensure the output directory exists
#         outdir = os.path.abspath(outdir_base)
#         os.makedirs(outdir, exist_ok=True)
        
#         # Local directory for log files
#         log_dir = os.path.abspath("logs")
#         os.makedirs(log_dir, exist_ok=True)
        
        # Determine the output location based on 'allinone' and 'split' flags
        # if procflags['allinone']:
        #     # Single output file case
        #     outfile = f"{outdir}/{sample_name}_output.root"
        #     log_file = f"{log_dir}/{sample_name}_output.log"
        #     command = f'./processnanoaod.py {indir} {outfile} {jobconfmod} {sample_name} > {log_file} 2>&1 &'
        # else:
        #     # Multiple output files, one per job
        #     for job_index in range(procflags['split']):
        #         job_outfile = f"{outdir}/{sample_name}_job{job_index + 1}.root"
        #         log_file = f"{log_dir}/{sample_name}_job{job_index + 1}.log"
                
        #         command = f'./processnanoaod.py {indir} {job_outfile} {jobconfmod} {sample_name} > {log_file} 2>&1 &'
        #         print(f"Submitting job with command: {command}")
        #         os.system(command)

    #     if procflags['allinone']:
    #         # Process all files into a single output file
    #         outfile = f"{outdir}/{sample_name}_output.root"
    #         log_file = f"{log_dir}/{sample_name}_output.log"
    #         command = f'./processnanoaod.py {indir} {outfile} {jobconfmod} {sample_name} > {log_file} 2>&1 &'
    #         print(f"Submitting job with command: {command}")
    #         os.system(command)
    #     else:
    #         # Process files into multiple output files, one per job
    #         for job_index in range(procflags['split']):
    #             job_outfile = f"{outdir}/{sample_name}_job{job_index + 1}.root"
    #             log_file = f"{log_dir}/{sample_name}_job{job_index + 1}.log"
    #             command = f'./processnanoaod.py {indir} {job_outfile} {jobconfmod} {sample_name} > {log_file} 2>&1 &'
    #             print(f"Submitting job with command: {command}")
    #             os.system(command)

    
    # pass


# if __name__=="__main__":
#     from argparse import ArgumentParser
#     parser = ArgumentParser(usage="%prog jobconfigmodule", description='submits skim jobs in background where the job '\
#         +' configuration python module name should be passedd')
#     parser.add_argument("jobconfmod")
#     args = parser.parse_args()

#     jobconfmod_fname = args.jobconfmod
#     # strip .py from the filename
#     jobconfmod = jobconfmod_fname.replace('.py', '')

#     submit(jobconfmod)
#     pass

if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser(usage="%prog jobconfigmodule", description='Submits skim jobs in background where the job configuration python module name should be passed')
    parser.add_argument("jobconfmod")
    args = parser.parse_args()

    jobconfmod_fname = args.jobconfmod
    jobconfmod = jobconfmod_fname.replace('.py', '')

    submit(jobconfmod)

