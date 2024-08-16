//============================================================================
// Name        : nanoaodrdataframe.cpp
// Author      : Suyong Choi
// Version     :
// Copyright   : suyong@korea.ac.kr, Korea University, Department of Physics
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "NanoAODAnalyzerrdframe.h"
#include "TopSemiLeptAnalyzer.h"
//#include "SkimEvents.h"
#include "TChain.h"

using namespace std;
using namespace ROOT;

int main(void) {

	TChain c1("Events");
	// c1.Add("/eos/uscms/store/user/snehshuc/2017/DYjetsM10to50_2017_skim.root"); // MC
	c1.Add("root://cmsxrootd.fnal.gov//store/mc/RunIISummer20UL17NanoAODv9/TTGamma_Hadronic_TuneCP5_13TeV-madgraph-pythia8/NANOAODSIM/106X_mc2017_realistic_v9-v1/270000/");
	// c1.Add("/uscms/home/snehshuc/nobackup/CMSSW_10_6_28/src/TTGammaSemiLep_13TeV/Skimming/GJets_HT100To200_2017_skim.root");
	// c1.Add("/uscms/home/snehshuc/nobackup/CMSSW_10_6_28/src/TTGammaSemiLep_13TeV/Skimming/Data_SingleEle_d_2017_skim_10of10.root");
	std::string sampleName = "TTGamma_Hadronic";
	// TopSemiLeptAnalyzer nanoaodrdf(&c1, "testout_data.root");
	TopSemiLeptAnalyzer nanoaodrdf(&c1, "testout.root",sampleName);
	nanoaodrdf.setParams(2017, "UL", -1);
	nanoaodrdf.setHLT();

	string goodjsonfname = "data/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt";
	string pileupfname = "data/LUM/2017_UL/puWeights.json";
	string pileuptag = "Collisions17_UltraLegacy_goldenJSON";
	string btvfname = "data/BTV/2017_UL/btagging.json";
	string btvtype = "deepJet_shape";
	string jercfname = "data/JERC/UL17_jerc.json";
	string jerctag = "Summer19UL17_V5_MC_L1L2L3Res_AK4PFchs";
	string jercunctag = "Summer19UL17_V5_MC_Total_AK4PFchs";
	string muon_roch_fname = "data/MUO/2017_UL/RoccoR2017UL.txt";
	string muon_fname = "data/MUO/2017_UL/muon_Z.json.gz";
	string muonHLTtype = "NUM_IsoMu27_DEN_CutBasedIdTight_and_PFIsoTight";
	string muonRECOtype = "NUM_TrackerMuons_DEN_genTracks";
	string muonIDtype = "NUM_MediumID_DEN_TrackerMuons";
	string muonISOtype = "NUM_TightRelIso_DEN_MediumID";
	string electron_fname = "data/EGM/2017_UL/electron.json.gz";
	string electron_reco_type = "RecoAbove20";
	string electron_id_type = "Tight";
	string photon_fname = "data/EGM/2017_UL/photon.json.gz";
	string photon_id_type = "Medium";

	nanoaodrdf.setupCorrections(goodjsonfname, pileupfname, pileuptag, btvfname, btvtype, muon_roch_fname, muon_fname, muonHLTtype, muonRECOtype, muonIDtype, muonISOtype, electron_fname, electron_reco_type, electron_id_type, photon_fname,photon_id_type, jercfname, jerctag, jercunctag);
    
	nanoaodrdf.setupObjects();
	nanoaodrdf.setupAnalysis();
	nanoaodrdf.run(false, "outputTree");
	// nanoaodrdf.run(true, "outputTree");

	return EXIT_SUCCESS;
}
