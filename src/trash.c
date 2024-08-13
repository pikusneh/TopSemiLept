
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// void NanoAODAnalyzerrdframe::loadBtagEff(const std::string& sampleName, const std::string& year) {
//     std::cout << "Loading btag efficiencies for " << sampleName << " in year " << year << std::endl;

//     std::string fName = "BtagSF/btag_efficiencies_" + year + ".root";
//     std::string effType = "Other";
//     if (sampleName.find("TTGamma") != std::string::npos || sampleName.find("TTbar") != std::string::npos) {
//         effType = "Top";
//     }

//     std::string leffName = effType + "_l_efficiency";
//     std::string ceffName = effType + "_c_efficiency";
//     std::string beffName = effType + "_b_efficiency";

//     TFile* inputFile = TFile::Open(fName.c_str(), "read");
//     if (!inputFile || inputFile->IsZombie()) {
//         std::cerr << "Error opening file: " << fName << std::endl;
//         return;
//     }

//     l_eff = dynamic_cast<TH2D*>(inputFile->Get(leffName.c_str()));
//     c_eff = dynamic_cast<TH2D*>(inputFile->Get(ceffName.c_str()));
//     b_eff = dynamic_cast<TH2D*>(inputFile->Get(beffName.c_str()));

//     if (!l_eff || !c_eff || !b_eff) {
//         std::cerr << "Error loading histograms from file: " << fName << std::endl;
//     }

//     inputFile->Close();
//     delete inputFile;
// }

// // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// double NanoAODAnalyzerrdframe::getBTaggingEff(double hadflav, double eta, double pt) {
//     TH2D* hist = nullptr;
//     if (hadflav != 0) { // b or c flavor
//         hist = (hadflav == 4 || hadflav == 5) ? b_eff : c_eff;
//     } else { // light flavor
//         hist = l_eff;
//     }

//     if (!hist) {
//         std::cerr << "Error: Histogram not loaded." << std::endl;
//         return 1.0; // default efficiency
//     }

//     int binX = hist->GetXaxis()->FindBin(eta);
//     int binY = hist->GetYaxis()->FindBin(pt);
//     binX = std::min(binX, hist->GetXaxis()->GetNbins());
//     binY = std::min(binY, hist->GetYaxis()->GetNbins());

//     return hist->GetBinContent(binX, binY);
// }

// ROOT::RDF::RNode NanoAODAnalyzerrdframe::calculateBTagSF(ROOT::RDF::RNode _rlm, std::vector<std::string> Jets_vars_names, int _case, const double btag_cut, std::string _BTaggingWP, std::string output_var) {
//     if (_case == 1) {
//         auto btagweightgenerator_bcflav_case1 = [this](const ROOT::VecOps::RVec<int>& hadflav, const ROOT::VecOps::RVec<float>& etas, const ROOT::VecOps::RVec<float>& pts, const ROOT::VecOps::RVec<float>& btag_scores, const double btag_cut, const std::string& _BTagWP, const std::string& variation) -> float {
//             double btagWeight_bcflav = 1.0;
//             for (std::size_t i = 0; i < pts.size(); i++) {
//                 if (std::abs(etas[i]) > 2.4999 || pts[i] < 30.000001 || hadflav[i] == 0) continue;
//                 if (btag_scores[i] >= btag_cut) {
//                     double bcjets_weights = _correction_btag1->at("deepJet_mujets")->evaluate({variation, _BTagWP, hadflav[i], std::fabs(etas[i]), pts[i]});
//                     btagWeight_bcflav *= bcjets_weights;
//                 } else {
//                     double bcjets_weights = _correction_btag1->at("deepJet_mujets")->evaluate({variation, _BTagWP, hadflav[i], std::fabs(etas[i]), pts[i]});
//                     double eff = getBTaggingEff(hadflav[i], etas[i], pts[i]);
//                     btagWeight_bcflav *= (1 - bcjets_weights * eff) / (1 - eff);
//                 }
//             }
//             return btagWeight_bcflav;
//         };

//         auto btagweightgenerator_lflav_case1 = [this](const ROOT::VecOps::RVec<int>& hadflav, const ROOT::VecOps::RVec<float>& etas, const ROOT::VecOps::RVec<float>& pts, const ROOT::VecOps::RVec<float>& btag_scores, const double btag_cut, const std::string& _BTagWP, const std::string& variation) -> float {
//             double btagWeight_lflav = 1.0;
//             for (std::size_t i = 0; i < pts.size(); i++) {
//                 if (std::abs(etas[i]) > 2.4999 || pts[i] < 30.000001 || hadflav[i] != 0) continue;
//                 if (btag_scores[i] >= btag_cut) {
//                     double lightjets_weights = _correction_btag1->at("deepJet_incl")->evaluate({variation, _BTagWP, hadflav[i], std::fabs(etas[i]), pts[i]});
//                     btagWeight_lflav *= lightjets_weights;
//                 } else {
//                     double lightjets_weights = _correction_btag1->at("deepJet_incl")->evaluate({variation, _BTagWP, hadflav[i], std::fabs(etas[i]), pts[i]});
//                     double eff = getBTaggingEff(hadflav[i], etas[i], pts[i]);
//                     btagWeight_lflav *= (1 - lightjets_weights * eff) / (1 - eff);
//                 }
//             }
//             return btagWeight_lflav;
//         };

//         std::vector<std::string> variations = {"central", "up", "down", "up_correlated", "down_correlated", "up_uncorrelated", "down_uncorrelated", "up_statistic", "down_statistic"};
//         for (const std::string& variation : variations) {
//             std::string column_name_bcflav = output_var + "bcflav_" + variation;
//             _rlm = _rlm.Define(column_name_bcflav, [btagweightgenerator_bcflav_case1, variation, btag_cut, _BTaggingWP](const ROOT::VecOps::RVec<int>& hadflav, const ROOT::VecOps::RVec<float>& etas, const ROOT::VecOps::RVec<float>& pts, const ROOT::VecOps::RVec<float>& btag_scores) {
//                 float weight = btagweightgenerator_bcflav_case1(hadflav, etas, pts, btag_scores, btag_cut, _BTaggingWP, variation);
//                 return weight;
//             }, Jets_vars_names);

//             std::string column_name_lflav = output_var + "lflav_" + variation;
//             _rlm = _rlm.Define(column_name_lflav, [btagweightgenerator_lflav_case1, variation, btag_cut, _BTaggingWP](const ROOT::VecOps::RVec<int>& hadflav, const ROOT::VecOps::RVec<float>& etas, const ROOT::VecOps::RVec<float>& pts, const ROOT::VecOps::RVec<float>& btag_scores) {
//                 float weight = btagweightgenerator_lflav_case1(hadflav, etas, pts, btag_scores, btag_cut, _BTaggingWP, variation);
//                 return weight;
//             }, Jets_vars_names);

//             std::cout << "BJet SF column name: " << column_name_bcflav << " and " << column_name_lflav << std::endl;
//         }
//     } else if (_case == 3) {
//         auto btagweightgenerator3 = [this](const ROOT::VecOps::RVec<int>& hadflav, const ROOT::VecOps::RVec<float>& etas, const ROOT::VecOps::RVec<float>& pts, const ROOT::VecOps::RVec<float>& btags) -> float {
//             double bweight = 1.0;
//             for (std::size_t i = 0; i < pts.size(); i++) {
//                 if (std::abs(etas[i]) > 2.5 || pts[i] < 30.000001) continue;
//                 double w = _correction_btag1->at(_btvtype)->evaluate({"central", hadflav[i], std::fabs(etas[i]), pts[i], btags[i]});
//                 bweight *= w;
//             }
//             return bweight;
//         };

//         std::string column_name = output_var + "case3";
//         _rlm = _rlm.Define(column_name, btagweightgenerator3, Jets_vars_names);
//         std::cout << "BJet SF column name: " << column_name << std::endl;
//     }
//     return _rlm;
// }


std::string output_btag_column_name = "btag_SF_";
  _rlm = calculateBTagSF(_rlm, Jets_vars_names, _case, 0.4506,"M",output_btag_column_name);
 _rlm = _rlm.Define("evWeight_wobtagSF", " pugenWeight * muon_SF_central * ele_SF_central"); 
  _rlm = _rlm.Define("totbtagSF", "btag_SF_bcflav_central * btag_SF_lflav_central"); 


  //Prefiring Weight for 2016 and 2017
  _rlm = applyPrefiringWeight(_rlm);

  //Total event Weight:
  _rlm = _rlm.Define("evWeight", " pugenWeight *prefiring_SF_central * btag_SF_bcflav_central * btag_SF_lflav_central * muon_SF_central * ele_SF_central"); 





"""
File contains job options 
"""


config = {
     
        'intreename': "Events",
        'outtreename': "outputTree2",
        'year': 2017,
        'runtype': 'UL',
        'datatype': -1,
        'goodjson': 'data/Legacy_RunII/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt', #UL_2017
        'pileupfname': 'data/LUM/2017_UL/puWeights.json',

        'pileuptag': 'Collisions17_UltraLegacy_goldenJSON',

        'btvfname': 'data/BTV/2017_UL/btagging.json',
    
        'btvtype': 'deepJet_mujets', #for fixed wp : case1 

        # Muon Correction #2017
        'muon_roch_fname': 'data/MUO/2017_UL/RoccoR2017UL.txt', 
        'muon_fname': 'data/MUO/2017_UL/muon_Z.json.gz', 
        'muon_HLT_type': 'NUM_IsoMu27_DEN_CutBasedIdTight_and_PFIsoTight',#'HLT UL scale factor',
        'muon_RECO_type': 'NUM_TrackerMuons_DEN_genTracks',#'RECO UL scale factor',
        'muon_ID_type': 'NUM_MediumID_DEN_TrackerMuons',#'ID UL scale factor',
        'muon_ISO_type': 'NUM_TightRelIso_DEN_MediumID',#'ISO UL scale factor',


         # Electron Correction 2017
        'electron_fname': 'data/EGM/2017_UL/electron.json.gz', 
        'electron_reco_type': 'RecoAbove20',
        'electron_id_type': 'Tight',#'Tight ID UL scale factor',
     
        # json file name for JERC 2017
        'jercfname': 'data/JERC/UL17_jerc.json',

        # conbined correction type for jets
        'jerctag': 'Summer19UL17_V5_MC_L1L2L3Res_AK4PFchs', 

        # jet uncertainty 
        'jercunctag': 'Summer19UL17_V5_MC_Total_AK4PFchs', 


        # json file name for JERC 2018
        # 'jercfname': 'data/JERC/jetUL18_jerc.json',


        # 'jerctag': 'Summer19UL18_V5_MC_L1L2L3Res_AK4PFchs', 
        # JER/jet resolution : Summer19UL18_JRV2_MC_PtResolution_AK4PFchs
        # jet uncertainty 
        # 'jercunctag': 'Summer19UL18_V5_MC_Total_AK4PFchs', 
        # JER/jetresolution scale factor: Summer19UL18_JRV2_MC_ScaleFactor_AK4PFchs
        
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
        #How many input files?
        'nrootfiles':10,
        }

nanoaod_inputdir_outputdir_pairs = [['/eos/uscms/store/mc/RunIISummer20UL17NanoAODv9/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/20UL17JMENano_106X_mc2017_realistic_v9-v1/40000', 'analyzed/output_DY.root', 'stderr.out']]

TTGamma_Dilepton,/TTGamma_Dilept_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM
TTGamma_Hadronic,/TTGamma_Hadronic_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM
TTGamma_SingleLept,/TTGamma_SingleLept_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM

TTGamma_Dilepton_Pt100,/TTGamma_Dilept_ptGamma100-200_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v3/NANOAODSIM
TTGamma_Dilepton_Pt200,/TTGamma_Dilept_ptGamma200inf_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM
TTGamma_SingleLept_Pt100,/TTGamma_SingleLept_ptGamma100-200_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM
TTGamma_SingleLept_Pt200,/TTGamma_SingleLept_ptGamma200inf_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM
TTGamma_Hadronic_Pt100,/TTGamma_Hadronic_ptGamma100-200_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM
TTGamma_Hadronic_Pt200,/TTGamma_Hadronic_ptGamma200inf_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v3/NANOAODSIM

TTbarPowheg_Dilepton,/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM
TTbarPowheg_Hadronic,/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM
TTbarPowheg_Semilept,/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM

W1jets,/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM
W2jets,/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM
W3jets,/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM
W4jets,/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM

DYjetsM10to50,/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM
DYjetsM50,/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM

ST_s_channel,/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM
ST_t_channel,/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM
ST_tbar_channel,/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM
ST_tW_channel,/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM
ST_tbarW_channel,/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM

Data_SingleMu_b,/SingleMuon/Run2017B-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD
Data_SingleMu_c,/SingleMuon/Run2017C-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD
Data_SingleMu_d,/SingleMuon/Run2017D-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD
Data_SingleMu_e,/SingleMuon/Run2017E-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD
Data_SingleMu_f,/SingleMuon/Run2017F-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD

Data_SingleEle_b,/SingleElectron/Run2017B-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD
Data_SingleEle_c,/SingleElectron/Run2017C-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD
Data_SingleEle_d,/SingleElectron/Run2017D-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD
Data_SingleEle_e,/SingleElectron/Run2017D-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD
Data_SingleEle_f,/SingleElectron/Run2017D-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD  





# input directory where your input root tree resides
# data='/eos/lyoeos.in2p3.fr/grid/cms/store/data/'
# filepath = '/eos/uscms/store/user/snehshuc/2017/'
# mc17 = '/eos/lyoeos.in2p3.fr/grid/cms/store/mc/RunIISummer20UL17NanoAODv9'
#outDir = '/eos/lyoeos.in2p3.fr/grid/cms/store/user/apurohit/SingleTop_Data_Oct2023_Results'
#outDir = '/eos/lyoeos.in2p3.fr/grid/cms/store/user/apurohit/SingleTop_MC_Results_Oct2023'
# outDir = '/eos/uscms/store/user/snehshuc/test/2017'
# output directory where your output should go
# dump of stderr/stdout to file
# nanoaod_inputdir_outputdir_pairs = [[filepath + 'DYjetsM10to50_2017_skim.root', 'test.root', 'outputest.root']]

# nanoaod_inputdir_outputdir_pairs = [['root://cmsxrootd.fnal.gov//store/mc/RunIISummer20UL17NanoAODv9/TTGamma_Hadronic_TuneCP5_13TeV-madgraph-pythia8/NANOAODSIM/106X_mc2017_realistic_v9-v1/270000/1B24CC21-60B4-894D-975A-E81AB88C1AE5.root', 'analyzed/TTgamma_output.root', 'stderr1.out']]

# nanoaod_inputdir_outputdir_pairs = [['root://cmsxrootd.fnal.gov//store/mc/RunIISummer20UL17NanoAODv9/TTGamma_Hadronic_TuneCP5_13TeV-madgraph-pythia8/NANOAODSIM/106X_mc2017_realistic_v9-v1/270000', '/eos/uscms/store/user/snehshuc/test/2017/TTGamma_Hadronic_output1.root', 'stderr_TTGamma_Had.out']]

# nanoaod_inputdir_outputdir_pairs = [['/TTGamma_Hadronic_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v1/NANOAODSIM','analyzed/TTGamma_Hadronic_pt_gamma100-200_output1.root', 'stderr_TTGamma_Had_ptgamma100-200.out']]

# nanoaod_inputdir_outputdir_pairs = [['/eos/uscms/store/mc/RunIISummer20UL17NanoAODv9/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/20UL17JMENano_106X_mc2017_realistic_v9-v1/40000', 'analyzed/output_DY.root', 'stderr.out']]

# nanoaod_inputdir_outputdir_pairs = [['/eos/uscms/store/user/snehshuc/2017/TTGamma', '/eos/uscms/store/user/snehshuc/test/2017/TTGamma_output_100k.root', 'stderr2.out']]

# ['/eos/lyoeos.in2p3.fr/grid/cms/store/mc/RunIISummer20UL17NanoAODv9/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/NANOAODSIM/106X_mc2017_realistic_v9-v1/80000/','analyzed/testcorrection_muon.root', 'stderr.out' ],
