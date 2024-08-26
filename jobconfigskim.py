"""
File contains job options 
"""
import os

def generate_input_output_pairs(sample_list_file):
    nanoaod_inputdir_outputdir_pairs = []
    sample_names = []
    
    with open(sample_list_file, 'r') as f:
        for line in f:
            if line.strip():  # Ensure the line is not empty
                sample_name, input_dir, output_file, stderr_file = line.strip().split(',')
                nanoaod_inputdir_outputdir_pairs.append([input_dir.strip(), output_file.strip(), stderr_file.strip()])
                sample_names.append(sample_name.strip())
    
    return nanoaod_inputdir_outputdir_pairs, sample_names

# options for Nanoaodrdframe
config = {
        # tree name of input file(s)
        'intreename': "Events",
        'outtreename': "outputTree",
        'year': 2017,
        'runtype': 'UL',
        'datatype': -1,
        }

# processing options
procflags = {
        # how many jobs?
        'split': 10, 
        # if False, one output file per input file, if True then one output file for everything
        'allinone': True, 
        # if True then skip existing analyzed files
        'skipold': True,
        # travel through the subdirectories and their subdirecties when processing.
        # becareful not to mix MC and real DATA in them.
        'recursive': True,
        # if False then only selected branches which is done in the .cpp file will be saved
        'saveallbranches': False,
        'nrootfiles': 'All'
        }

# input directory where your input root tree resides
# output directory wheere your output should go
# dump of stderr/stdout to file

# nanoaod_inputdir_outputdir_pairs = [['root://cmsxrootd.fnal.gov//store/mc/RunIISummer20UL17NanoAODv9/TTGamma_Hadronic_TuneCP5_13TeV-madgraph-pythia8/NANOAODSIM/106X_mc2017_realistic_v9-v1/270000/1B24CC21-60B4-894D-975A-E81AB88C1AE5.root', 'analyzed/TTGamma_Hadronic_Skim_2017.root', 'stderrSkim.out']]

# nanoaod_inputdir_outputdir_pairs = [['/TTGamma_Hadronic_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM','analyzed/TTGamma_Hadronic_Skim_output1.root', 'stderr_TTGamma_Had_Skim.out']]

sample_list_file = 'skimfile.txt'
nanoaod_inputdir_outputdir_pairs, sample_names = generate_input_output_pairs(sample_list_file)


