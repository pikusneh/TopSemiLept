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
       
        'intreename': "Events",  # tree name of input file(s)
        'outtreename': "outputTree2", # tree name of output file(s) it cannot be the same as the input tree name or it'll crash
        'year': 2017,    #data year (2016,2017,2018)
        'runtype': 'UL',   # is ReReco or Ultra Legacy
        'datatype': -1,

        #for correction
        # 'goodjson': 'data/Legacy_RunII/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt', #UL_2018
        'goodjson': 'data/Legacy_RunII/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt', #UL_2017  # good json file 

        # 'pileupfname': 'data/LUM/2018_UL/puWeights.json',
        'pileupfname': 'data/LUM/2017_UL/puWeights.json',  # pileup weight for MC 

        # 'pileuptag': 'Collisions18_UltraLegacy_goldenJSON',
        'pileuptag': 'Collisions17_UltraLegacy_goldenJSON',

        # json filename for BTV correction 
        # 'btvfname': 'data/BTV/2018_UL/btagging.json',
        'btvfname': 'data/BTV/2017_UL/btagging.json',
        # BTV correction type: //to use btvtype from the json file for the btag SFs
        'btvtype': 'deepJet_mujets', #for fixed wp : case1 # need to account for btag SF as deepCSV is used.
        #'btvtype': 'deepJet_comb', #for fixed wp : case2
        #'btvtype': 'deepJet_shape', #for central shape : case3
        
        # Muon Correction #2018
        # 'muon_fname': 'data/MUON/2018_UL/muon_Z.json', #2018
        # 'muontype': 'NUM_MediumID_DEN_TrackerMuons',#'Medium ID UL scale factor',
        #'muontype': 'NUM_TightRelIso_DEN_MediumID',#'Medium ISO UL scale factor',

        # Muon Correction #2017
        'muon_roch_fname': 'data/MUO/2017_UL/RoccoR2017UL.txt', 
        'muon_fname': 'data/MUO/2017_UL/muon_Z.json.gz', 
        'muon_HLT_type': 'NUM_IsoMu27_DEN_CutBasedIdTight_and_PFIsoTight',#'HLT UL scale factor',
        'muon_RECO_type': 'NUM_TrackerMuons_DEN_genTracks',#'RECO UL scale factor',
        'muon_ID_type': 'NUM_MediumID_DEN_TrackerMuons',#'ID UL scale factor',
        'muon_ISO_type': 'NUM_TightRelIso_DEN_MediumID',#'ISO UL scale factor',
        #'muontype': 'NUM_TightRelIso_DEN_MediumID',#'Medium ISO UL scale factor',

         # Electron Correction 2017
        'electron_fname': 'data/EGM/2017_UL/electron.json.gz', 
        'electron_reco_type': 'RecoAbove20',
        'electron_id_type': 'Tight',#'Tight ID UL scale factor',

        # Photon Correction 2017
        'photon_fname':'data/EGM/2017_UL/photon.json.gz',
        'photon_id_type':'Medium',
     
        # json file name for JERC 2017
        'jercfname': 'data/JERC/UL17_jerc.json',

        # conbined correction type for jets
        'jerctag': 'Summer19UL17_V5_MC_L1L2L3Res_AK4PFchs', 

        # jet uncertainty 
        'jercunctag': 'Summer19UL17_V5_MC_Total_AK4PFchs', 


        # json file name for JERC 2018
        # 'jercfname': 'data/JERC/jetUL18_jerc.json',

        # combined correction type for jets
        # 'jerctag': 'Summer19UL18_V5_MC_L1L2L3Res_AK4PFchs', 
        # JER/jet resolution : Summer19UL18_JRV2_MC_PtResolution_AK4PFchs
        # jet uncertainty 
        # 'jercunctag': 'Summer19UL18_V5_MC_Total_AK4PFchs', 
        # JER/jetresolution scale factor: Summer19UL18_JRV2_MC_ScaleFactor_AK4PFchs
        
        }

# processing options
procflags = {
     
        'split': 10,    # how many jobs?
        # 'n_jobs': 10,
        'allinone': False,   # if False, one output file per input file, if True then one output file for everything
        'skipold': True,    # if True then skip existing analyzed files
        'recursive': True, # travel through the subdirectories and their subdirecties when processing. # becareful not to mix MC and real DATA in them.                        
        'saveallbranches': False, # if False then only selected branches which is done in the .cpp file will be saved
        #How many input files?
        'nrootfiles': 'All', # set to -1 when you want to process all files in the input dir of root:// type
        }


sample_list_file = 'test_list.txt'
nanoaod_inputdir_outputdir_pairs, sample_names = generate_input_output_pairs(sample_list_file)



