"""
File contains job options 
"""

# options for Nanoaodrdframe
config = {
        # tree name of input file(s)
        'intreename': "Events", 
        # tree name of output file(s) it cannot be the same as the input tree name or it'll crash
        'outtreename': "outputTree", 
        # good json file
        # 'goodjson': 'data/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt',

        # # pileup weight for MC
        # 'pileupfname': 'data/LUM/2016postVFP_UL/puWeights.json',
        # #'pileupfname': 'data/LUM/2017_UL/puWeights.json',
        # 'pileuptag': 'Collisions16_UltraLegacy_goldenJSON',
        # #'pileuptag': 'Collisions17_UltraLegacy_goldenJSON',

        # # json filename for BTV correction
        # 'btvfname': 'data/BTV/2016postVFP_UL/btagging.json',
        # #'btvfname': 'data/BTV/2017_UL/btagging.json',
        # # BTV correction type
        # 'btvtype': 'deepJet_shape',

        # # json file name for JERC
        # 'jercfname': 'data/JERC/UL16postVFP_jerc.json',
        # #'jercfname': 'data/JERC/UL17_jerc.json',
        # # conbined correction type for jets
        # 'jerctag': 'Summer19UL16_V7_MC_L1L2L3Res_AK4PFchs', 
        # #'jerctag': 'Summer19UL17_V5_MC_L1L2L3Res_AK4PFchs', 
        # # jet uncertainty 
        # 'jercunctag': 'Summer19UL16_V7_MC_Total_AK4PFchs', 
        # #'jercunctag': 'Summer19UL17_V5_MC_Total_AK4PFchs', 
        }

# processing options
procflags = {
        # how many jobs?
        'split': 1, 
        # if False, one output file per input file, if True then one output file for everything
        'allinone': True, 
        # if True then skip existing analyzed files
        'skipold': True,
        # travel through the subdirectories and their subdirecties when processing.
        # becareful not to mix MC and real DATA in them.
        'recursive': True,
        # if False then only selected branches which is done in the .cpp file will be saved
        'saveallbranches': False,
        }

# input directory where your input root tree resides
# output directory wheere your output should go
# dump of stderr/stdout to file

# nanoaod_inputdir_outputdir_pairs = [['root://cmsxrootd.fnal.gov//store/mc/RunIISummer20UL17NanoAODv9/TTGamma_Hadronic_TuneCP5_13TeV-madgraph-pythia8/NANOAODSIM/106X_mc2017_realistic_v9-v1/270000/1B24CC21-60B4-894D-975A-E81AB88C1AE5.root', 'analyzed/TTGamma_Hadronic_Skim_2017.root', 'stderrSkim.out']]

# nanoaod_inputdir_outputdir_pairs = [['/eos/uscms/store/mc/RunIISummer20UL17NanoAODv9/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/20UL17JMENano_106X_mc2017_realistic_v9-v1/40000', 'analyzed/output_skim_DY.root', 'stderrSkimDY.out']]

nanoaod_inputdir_outputdir_pairs = [['/TTGamma_Hadronic_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM','/eos/uscms/store/user/snehshuc/test/2017/TTGamma_Hadronic_Skim_output1.root', 'stderr_TTGamma_Had_Skim.out']]


# nanoaod_inputdir_outputdir_pairs = [
#     ['testinputdata/MC/2016', 'processed/2016/test.root', 'stderrout.out' ],
#     #['processed/','analyzed/tt.root', 'stderrout.out' ],
# ]

