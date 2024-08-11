/*
 * TopSemiLeptAnalyzer.cpp
 *
 *  Created on: May 6, 2022
 *      Author: suyong
 *      Developper: cdozen
 */

#include "Math/GenVector/VectorUtil.h"
#include "TopSemiLeptAnalyzer.h"
#include "utility.h"
#include <fstream>
#include "correction.h"
using correction::CorrectionSet;

TopSemiLeptAnalyzer::TopSemiLeptAnalyzer(TTree *t, std::string outfilename)
:NanoAODAnalyzerrdframe(t, outfilename)
{
     HLT2017Names= {"HLT_IsoMu24","HLT_IsoMu24_eta2p1","HLT_IsoMu27","HLT_Mu50","HLT_OldMu100","HLT_TkMu100","HLT_Ele32_WPTight_Gsf_L1DoubleEG","HLT_Ele32_WPTight_Gsf","HLT_Ele35_WPTight_Gsf","HLT_Ele115_CaloIdVT_GsfTrkIdT"};
    
}

// Define your cuts here
void TopSemiLeptAnalyzer::defineCuts() {
    if (debug) {
        std::cout << "================================//=================================" << std::endl;
        std::cout << "Line : " << __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout << "================================//=================================" << std::endl;
    }

    auto Nentry = _rlm.Count();
    // _rlm = _rlm.Range(0, 100000);
    // auto Nentry_100 = _rlm.Count();
    std::cout << "-------------------------------------------------------------------" << std::endl;
    std::cout << "Usage of ranges:\n"
              << " - All entries: " << *Nentry << std::endl;
            //   << " - Entries from 0 to 100: " << *Nentry_100 << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;

    // Apply HLT trigger cuts for both electron and muon channels
    addCuts("HLT_Ele32_WPTight_Gsf || HLT_IsoMu24", "1");  

    // Ensure at least one muon or electron
    addCuts("nMuon > 0 || nElectron > 0", "2");

    // Ensure exactly one tight lepton
    addCuts("NtightMuons + NtightElectrons == 1", "3");

    // // // Ensure at least three jets
    // addCuts("NgoodJets >= 3", "4");

    // // // Ensure at least one b-jet
    // addCuts("Ngood_bjets >= 1", "5");
}

void TopSemiLeptAnalyzer::selectElectrons()
{
    cout << "select good electrons" << endl;
    if (debug){
    std::cout<< "================================//=================================" << std::endl;
    std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
    std::cout<< "================================//=================================" << std::endl;
    }
    // _rlm = _rlm.Define("ElectronSC","abs(Electron_eta+Electron_deltaEtaSC)<1.442 || abs(Electron_eta+Electron_deltaEtaSC)>1.566");
    _rlm = _rlm.Define("ElectronSC", [](const ROOT::VecOps::RVec<float>& eta, const ROOT::VecOps::RVec<float>& deltaEtaSC) {
        ROOT::VecOps::RVec<float> sc(eta.size());
        for (size_t i = 0; i < eta.size(); ++i) {
            sc[i] = std::abs(eta[i] + deltaEtaSC[i]);
        }
        return sc;
    }, {"Electron_eta", "Electron_deltaEtaSC"});
     
      // Define a condition to select electrons based on the supercluster eta
    auto scCondition = [](const ROOT::VecOps::RVec<float>& sc) {
        ROOT::VecOps::RVec<bool> passCondition(sc.size(), false);
        for (size_t i = 0; i < sc.size(); ++i) {
            passCondition[i] = sc[i] < 1.442 || sc[i] > 1.566;
        }
        return passCondition;
    };

    _rlm = _rlm.Define("ElectronSCCondition", scCondition, {"ElectronSC"});


   // Define ElectronsD0DzCut based on Dxy and Dz cuts for barrel and endcap
    auto d0dzCut = [](const ROOT::VecOps::RVec<float>& ElectronSC, const ROOT::VecOps::RVec<float>& Electron_dxy, const ROOT::VecOps::RVec<float>& Electron_dz) {
        ROOT::VecOps::RVec<bool> passCuts(ElectronSC.size(), false);
        for (size_t i = 0; i < ElectronSC.size(); ++i) {
            bool passDxy = (ElectronSC[i] < 1.479 && std::abs(Electron_dxy[i]) < 0.05) || (ElectronSC[i] >= 1.479 && std::abs(Electron_dxy[i]) < 0.1);
            bool passDz = (ElectronSC[i] < 1.479 && std::abs(Electron_dz[i]) < 0.1) || (ElectronSC[i] >= 1.479 && std::abs(Electron_dz[i]) < 0.2);
            passCuts[i] = passDxy && passDz;
        }
        return passCuts;
    };

    _rlm = _rlm.Define("ElectronsD0DzCut", d0dzCut, {"ElectronSC", "Electron_dxy", "Electron_dz"});


    // Tight electrons definition
    _rlm = _rlm.Define("tightElectronsID", ElectronID(4))
               .Define("tightElectrons", "Electron_pt>=35.0 && abs(Electron_eta)<2.4 && tightElectronsID && ElectronsD0DzCut && ElectronSCCondition ")
               .Define("tightElectrons_pt", "Electron_pt[tightElectrons]")
               .Define("tightElectrons_eta", "Electron_eta[tightElectrons]")
               .Define("tightElectrons_phi", "Electron_phi[tightElectrons]")
               .Define("tightElectrons_mass", "Electron_mass[tightElectrons]")
               .Define("tightElectrons_idx", ::good_idx, {"tightElectrons"})
               .Define("NtightElectrons", "int(tightElectrons_pt.size())")
               .Define("tightElectrons_charge", "Electron_charge[tightElectrons]")
               .Define("ElectronIsOSSF", "(NtightElectrons - abs(Sum(tightElectrons_charge)))/2")
               .Define("tightElectron_4Vecs", ::generate_4vec, {"tightElectrons_pt", "tightElectrons_eta", "tightElectrons_phi", "tightElectrons_mass"});


   // Veto electrons definition
    _rlm = _rlm.Define("vetoElectronsID", ElectronID(1))
               .Define("vetoElectrons", " Electron_pt>15.0 && abs(Electron_eta)<2.4 && vetoElectronsID && ElectronsD0DzCut ")
               .Define("vetoElectrons_pt", "Electron_pt[vetoElectrons]")
               .Define("vetoElectrons_eta", "Electron_eta[vetoElectrons]")
               .Define("vetoElectrons_phi", "Electron_phi[vetoElectrons]")
               .Define("vetoElectrons_mass", "Electron_mass[vetoElectrons]")
               .Define("NvetoElectrons", "int(vetoElectrons_pt.size())")
               .Define("vetoElectrons_4Vecs", ::generate_4vec, {"vetoElectrons_pt", "vetoElectrons_eta", "vetoElectrons_phi", "vetoElectrons_mass"});
  
    
    _rlm = _rlm.Define("goodElectronsID", ElectronID(2)); //without pt-eta cuts
	_rlm = _rlm.Define("goodElectrons", "goodElectronsID && Electron_pt>30.0 && abs(Electron_eta)<2.4 && Electron_pfRelIso03_all<0.15");
    _rlm = _rlm.Define("goodElectrons_pt", "Electron_pt[goodElectrons]")
                .Define("goodElectrons_eta", "Electron_eta[goodElectrons]")
                .Define("goodElectrons_phi", "Electron_phi[goodElectrons]")
                .Define("goodElectrons_mass", "Electron_mass[goodElectrons]")
                .Define("goodElectrons_idx", ::good_idx, {"goodElectrons"})
                .Define("NgoodElectrons", "int(goodElectrons_pt.size())");
    _rlm = _rlm.Define("goodElectron_4Vecs", ::generate_4vec, {"goodElectrons_pt", "goodElectrons_eta", "goodElectrons_phi", "goodElectrons_mass"});

}

void TopSemiLeptAnalyzer::selectMuons()
{

    cout << "select good muons" << endl;
    // if (debug){
    //     std::cout<< "================================//=================================" << std::endl;
    //     std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
    //     std::cout<< "================================//=================================" << std::endl;
    // }

    // Tight muon selection
    _rlm = _rlm.Define("tightMuonsID", MuonID(4));
    _rlm = _rlm.Define("tightMuons", "Muon_pt>30.0 && abs(Muon_eta)<2.4 && tightMuonsID && Muon_miniPFRelIso_all <= 0.15")
               .Define("tightMuons_pt", "Muon_pt[tightMuons]")
               .Define("tightMuons_eta", "Muon_eta[tightMuons]")
               .Define("tightMuons_phi", "Muon_phi[tightMuons]")
               .Define("tightMuons_mass", "Muon_mass[tightMuons]")
               .Define("tightMuons_charge", "Muon_charge[tightMuons]")
               .Define("tightMuons_idx", ::good_idx, {"tightMuons"})
               .Define("NtightMuons", "int(tightMuons_pt.size())")
               .Define("MuonIsOSSF", "(NtightMuons - abs(Sum(tightMuons_charge)))/2")
               .Define("tightMuons_4vecs", ::generate_4vec, {"tightMuons_pt", "tightMuons_eta", "tightMuons_phi", "tightMuons_mass"});


    // Veto muon selection
    _rlm = _rlm.Define("vetoMuonsID", MuonID(1));
    _rlm = _rlm.Define("vetoMuons", "Muon_pt>15.0 && abs(Muon_eta)<2.4 && vetoMuonsID && Muon_miniPFRelIso_all <= 0.25")
               .Define("vetoMuons_pt", "Muon_pt[vetoMuons]")
               .Define("vetoMuons_eta", "Muon_eta[vetoMuons]")
               .Define("vetoMuons_phi", "Muon_phi[vetoMuons]")
               .Define("vetoMuons_mass", "Muon_mass[vetoMuons]")
               .Define("NvetoMuons", "int(vetoMuons_pt.size())")
               .Define("vetoMuons_4vecs", ::generate_4vec, {"vetoMuons_pt", "vetoMuons_eta", "vetoMuons_phi", "vetoMuons_mass"});

    // Good muon selection
    _rlm = _rlm.Define("goodMuonsID", MuonID(2)); //loose muons
    _rlm = _rlm.Define("goodMuons","goodMuonsID && Muon_pt > 30 && abs(Muon_eta) < 2.4 && Muon_miniPFRelIso_all < 0.40");
    _rlm = _rlm.Define("goodMuons_pt", "Muon_pt[goodMuons]") 
                .Define("goodMuons_eta", "Muon_eta[goodMuons]")
                .Define("goodMuons_phi", "Muon_phi[goodMuons]")
                .Define("goodMuons_mass", "Muon_mass[goodMuons]")
                .Define("goodMuons_charge", "Muon_charge[goodMuons]")
                .Define("goodMuons_idx", ::good_idx, {"goodMuons"})
                .Define("NgoodMuons", "int(goodMuons_pt.size())");

    _rlm = _rlm.Define("goodMuons_4vecs", ::generate_4vec, {"goodMuons_pt", "goodMuons_eta", "goodMuons_phi", "goodMuons_mass"});
   

}
//=================================Select Jets=================================================//
//check the twiki page :    https://twiki.cern.ch/twiki/bin/view/CMS/JetID
//to find jetId working points for the purpose of  your analysis.
    //jetId==2 means: pass tight ID, fail tightLepVeto
    //jetId==6 means: pass tight ID and tightLepVeto ID.
//=============================================================================================//
void TopSemiLeptAnalyzer::selectJets()
{
    cout << "select good jets" << endl;
    // Check if the Jet_hadronFlavour branch exists
    if (_atree->GetBranch("Jet_hadronFlavour") == nullptr) {
        std::cout << "Jet_hadronFlavour branch is not found in the input file!!" << std::endl;
    } else {
        std::cout << "Jet_hadronFlavour branch is found in the input file." << std::endl;
    }

    // Define goodJetsID, goodJets and other goodJets-related variables
    _rlm = _rlm.Define("goodJetsID", JetID(6)); // without pt-eta cuts
    _rlm = _rlm.Define("goodJets", "goodJetsID && Jet_pt > 30.0 && abs(Jet_eta) < 2.4");
    _rlm = _rlm.Define("goodJets_pt", "Jet_pt[goodJets]")
               .Define("goodJets_eta", "Jet_eta[goodJets]")
               .Define("goodJets_phi", "Jet_phi[goodJets]")
               .Define("goodJets_mass", "Jet_mass[goodJets]")
               .Define("goodJets_idx", ::good_idx, {"goodJets"});

    // Define goodJets_hadflav if the branch exists
    if (_atree->GetBranch("Jet_hadronFlavour") != nullptr) {
        _rlm = _rlm.Define("goodJets_hadflav", "Jet_hadronFlavour[goodJets]");
    }

      _rlm = _rlm.Define("goodJets_btag","Jet_btagDeepB[goodJets]")  //JetDeepCSV
                .Define("NgoodJets","int(goodJets_pt.size())")
                .Define("goodJets_4vecs", ::generate_4vec, {"goodJets_pt", "goodJets_eta", "goodJets_phi", "goodJets_mass"});

      _rlm = _rlm.Define("btagcuts", "goodJets_btag>0.4506") //medium wp for 2017
			.Define("good_bjetpt", "goodJets_pt[btagcuts]")
			.Define("good_bjeteta", "goodJets_eta[btagcuts]")
			.Define("good_bjetphi", "goodJets_phi[btagcuts]")
			.Define("good_bjetmass", "goodJets_mass[btagcuts]")
			.Define("good_bjetdeepcsvjet", "goodJets_btag[btagcuts]");
	
    if (_atree->GetBranch("Jet_hadronFlavour") != nullptr) {
        _rlm = _rlm.Define("good_bjethadflav", "goodJets_hadflav[btagcuts]");
    }
			
	_rlm = _rlm.Define("Ngood_bjets", "int(good_bjetpt.size())")
			.Define("good_bjet4vecs", ::generate_4vec, {"good_bjetpt", "good_bjeteta", "good_bjetphi", "good_bjetmass"});


}
//=================================Overlap function=================================================//
void TopSemiLeptAnalyzer::removeOverlaps()
{
    cout << "checking overlapss between jets and muons" << endl;
	// lambda function
	// for checking overlapped jets with leptons
    auto checkoverlap = [](FourVectorVec &goodjets, FourVectorVec &goodlep)
		{
			doubles mindrlepton;
			for (auto ajet: goodjets)
			{
                auto mindr = 6.0;
				for (auto alepton: goodlep)
				{
					auto dr = ROOT::Math::VectorUtil::DeltaR(ajet, alepton);
                    if (dr < mindr) mindr = dr;
                }
                int out = mindr > 0.4 ? 1 : 0;
                mindrlepton.emplace_back(out);

			}
            return mindrlepton;
	    };
	//cout << "overlap removal" << endl;
    //==============================Clean Jets==============================================//
    //Use clean jets/bjets for object selections
    //=====================================================================================//
     bool hasJetHadronFlavour = (_atree->GetBranch("Jet_hadronFlavour") != nullptr);

    _rlm = _rlm.Define("muonjetoverlap", checkoverlap, {"goodJets_4vecs","tightMuons_4vecs"});
	_rlm =	_rlm.Define("Selected_jetpt", "goodJets_pt[muonjetoverlap]")
		.Define("Selected_jeteta", "goodJets_eta[muonjetoverlap]")
		.Define("Selected_jetphi", "goodJets_phi[muonjetoverlap]")
		.Define("Selected_jetmass", "goodJets_mass[muonjetoverlap]")
        .Define("Selected_jetbtag", "goodJets_btag[muonjetoverlap]")
		.Define("ncleanjetspass", "int(Selected_jetpt.size())")
		.Define("cleanjet4vecs", ::generate_4vec, {"Selected_jetpt", "Selected_jeteta", "Selected_jetphi", "Selected_jetmass"})
		.Define("Selected_jetHT", "Sum(Selected_jetpt)");

        if (hasJetHadronFlavour) {
             _rlm = _rlm.Define("Selected_jethadflav", "goodJets_hadflav[muonjetoverlap]");}
    
     //==============================Clean b-Jets==============================================// 
	 //--> after remove overlap: use requested btaggedJets for btag-weight SFs && weight_generator. 
	 //=====================================================================================//
	_rlm = _rlm.Define("btagcuts2", "Selected_jetbtag>0.4506") //medium wp 
			.Define("Selected_bjetpt", "Selected_jetpt[btagcuts2]")
			.Define("Selected_bjeteta", "Selected_jeteta[btagcuts2]")
			.Define("Selected_bjetphi", "Selected_jetphi[btagcuts2]")
			.Define("Selected_bjetmass", "Selected_jetmass[btagcuts2]")
			.Define("ncleanbjetspass", "int(Selected_bjetpt.size())")
			.Define("Selected_bjetHT", "Sum(Selected_bjetpt)")
			.Define("cleanbjet4vecs", ::generate_4vec, {"Selected_bjetpt", "Selected_bjeteta", "Selected_bjetphi", "Selected_bjetmass"});    

    if (hasJetHadronFlavour) {
    _rlm = _rlm.Define("Selected_bjethadflav", "Selected_jethadflav[btagcuts2]");   }    

}

void TopSemiLeptAnalyzer::calculateEvWeight(){
	
  int _case = 1;
    std::vector<std::string> Jets_vars_names = {"Selected_jethadflav", "Selected_jeteta",  "Selected_jetpt"};  
  if(_case !=1){
    Jets_vars_names.emplace_back("Selected_jetbtag");
  }
  std::string output_btag_column_name = "btag_SF_";
  _rlm = calculateBTagSF(_rlm, Jets_vars_names, _case ,output_btag_column_name);
 
//   std::vector<std::string> Muon_vars_names = {"goodMuons_eta", "goodMuons_pt"};
std::vector<std::string> Muon_vars_names = {"tightMuons_eta", "tightMuons_pt"};
  std::string output_mu_column_name = "muon_SF_";
  _rlm = calculateMuSF(_rlm, Muon_vars_names, output_mu_column_name);

//   std::vector<std::string> Electron_vars_names = {"goodElectrons_eta", "goodElectrons_pt"};
  std::vector<std::string> Electron_vars_names = {"tightElectrons_eta", "tightElectrons_pt"};
  std::string output_ele_column_name = "ele_SF_";
  _rlm = calculateEleSF(_rlm, Electron_vars_names, output_ele_column_name);
//   _rlm = _rlm.Define("evWeight", " pugenWeight * muon_SF_central * ele_SF_central"); 
//   _rlm = _rlm.Define("totbtagSF", "btag_SF_bcflav_central * btag_SF_lflav_central"); 


  //Prefiring Weight for 2016 and 2017
//   _rlm = applyPrefiringWeight(_rlm);

  //Total event Weight:
//   _rlm = _rlm.Define("evWeight", " pugenWeight *prefiring_SF_central * btag_SF_bcflav_central * btag_SF_lflav_central * muon_SF_central * ele_SF_central");
_rlm = _rlm.Define("evWeight", " pugenWeight * btag_SF_central * muon_SF_central * ele_SF_central");

}
//MET

void TopSemiLeptAnalyzer::selectMET()
{
    if (debug){
        std::cout<< "================================//=================================" << std::endl;
        std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout<< "================================//=================================" << std::endl;
    }

    // _rlm = _rlm.Define("goodMET_sumET","MET_sumEt>800")
            _rlm = _rlm.Define("goodMET_pt","MET_pt>5");
    //             .Define("goodMET_eta","MET_eta[goodMET]")
    //             .Define("goodMET_phi","MET_phi[goodMET]")
    //             .Define("NgoodMET","int(goodMET_pt.size())");
    // _rlm = _rlm.Define("goodMet", "MET_sumEt>600 && MET_pt>5");
    // _rlm = _rlm.Define("goodMet_pt", "MET_pt[goodMet]");

    
}

//=============================define variables==================================================//
void TopSemiLeptAnalyzer::defineMoreVars()
{
    if (debug){
        std::cout<< "================================//=================================" << std::endl;
        std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout<< "================================//=================================" << std::endl;
    }

    addVar({"good_muon1pt", "goodMuons_pt[0]", ""});
    addVar({"tight_muon1pt", "tightMuons_pt[0]", ""});

    //selected jet candidates
    addVar({"good_jet1pt", "(goodJets_pt.size()>0) ? goodJets_pt[0] : -1", ""});
    addVar({"Selected_jet1pt", "(Selected_jetpt.size()>0) ? Selected_jetpt[0] : -1", ""});
    addVar({"good_jet1eta", "goodJets_eta[0]", ""});
    addVar({"good_jet1mass", "goodJets_mass[0]", ""});

    //================================Store variables in tree=======================================//
    addVartoStore("run");
    addVartoStore("luminosityBlock");
    addVartoStore("event");
    addVartoStore("evWeight");

    // addVartoStore("genWeight");
    // addVartoStore("genEventSumw");

    //electron
    addVartoStore("nElectron");
    addVartoStore("Electron_pt");
    addVartoStore("Electron_eta");
    addVartoStore("Electron_charge");
    addVartoStore("NgoodElectrons");
    addVartoStore("goodElectrons_pt");
    addVartoStore("goodElectrons_eta");
    addVartoStore("NtightElectrons");
    addVartoStore("tightElectrons_pt");
    addVartoStore("tightElectrons_eta");


    //muon
    addVartoStore("nMuon");
    addVartoStore("Muon_charge");
    addVartoStore("Muon_pt");
    addVartoStore("Muon_eta");
    addVartoStore("Muon_mass");
    addVartoStore("NgoodMuons");
    addVartoStore("goodMuons_pt");
    addVartoStore("goodMuons_eta");
    addVartoStore("NtightMuons");
    addVartoStore("tightMuons_pt");
    addVartoStore("tightMuons_eta");

    //jet
    addVartoStore("nJet");
    addVartoStore("Jet_pt");
    addVartoStore("NgoodJets");
    addVartoStore("goodJets_pt");
    addVartoStore("Selected_jetpt");
	addVartoStore("Selected_jeteta");
	addVartoStore("Selected_jetbtag");

    addVartoStore("good_bjetdeepcsvjet");
    addVartoStore("Ngood_bjets");

    if (_atree->GetBranch("Jet_hadronFlavour") != nullptr) {
        addVartoStore("Selected_jethadflav");
        addVartoStore("goodJets_hadflav");
        addVartoStore("good_bjethadflav");
        addVartoStore("Selected_bjethadflav");
    }
	//jetmet corr
    addVartoStore("Jet_pt_corr");
	addVartoStore("Jet_pt_corr_up");
	addVartoStore("Jet_pt_corr_down");
	addVartoStore("Jet_pt_relerror");
    addVartoStore("MET_pt_corr");
    addVartoStore("MET_pt");
    addVartoStore("MET_phi");
    // addVartoStore("Photon_pt");
    
    if (!_isData) {
	//case1 btag correction- fixed wp	
	addVartoStore("btag_SF_central");
    // addVartoStore("btag_SF_bcflav_central");
    // addVartoStore("btag_SF_lflav_central");
    // addVartoStore("totbtagSF");
    // addVartoStore("evWeight_wobtagSF");
	addVartoStore("btag_SF_up");
	addVartoStore("btag_SF_down");
	
	//case3 shape correction
	//addVartoStore("btagWeight_case3");

	//MUONID - ISO SF & WEIGHT	
	addVartoStore("muon_SF_central");
	//addVartoStore("muon_id_weight");
	addVartoStore("muon_SF_id_sf");
	addVartoStore("muon_SF_id_syst");
	addVartoStore("muon_SF_id_systup");
	addVartoStore("muon_SF_id_systdown");
	//addVartoStore("muonISO_SF");
	addVartoStore("muon_SF_iso_sf");

    addVartoStore("ele_SF_central");
    addVartoStore("ele_SF_id_sf");
    addVartoStore("ele_SF_id_sfup");
    addVartoStore("ele_SF_id_sfdown");

	addVartoStore("evWeight");  }

    if (!_isData) { // Only add gen-level information for MC data, gen-level name is changed to avoid conflict
        addVartoStore("GenPartpt");
        addVartoStore("GenParteta");
        addVartoStore("GenPartphi");
        addVartoStore("GenPartmass");
        addVartoStore("GenPartpdgId");
        addVartoStore("nGenPart");
        std::cout << "Gen-level variables added." << std::endl;
    } 

}
void TopSemiLeptAnalyzer::bookHists()
{
    //=================================structure of histograms==============================================//
    //add1DHist( {"hnevents", "hist_title; x_axis title; y_axis title", 2, -0.5, 1.5}, "one", "evWeight", "");
    //add1DHist( {"hgoodelectron1_pt", "good electron1_pt; #electron p_{T}; Entries / after ", 18, -2.7, 2.7}, "good_electron1pt", "evWeight", "0");
    //======================================================================================================//
    
    if (debug){
        std::cout<< "================================//=================================" << std::endl;
        std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout<< "================================//=================================" << std::endl;
    }
    
    //================================gen/LHE weights======================================================//
   // if(!_isData && !isDefined("genWeight")){
   //     add1DHist({"hgenWeight", "genWeight", 1001, -100, 100}, "genWeight", "one", "");
    
    /*if(isDefined("LHEWeight_originalXWGTUP")){
        add1DHist({"hLHEweight", "LHEweight", 1001, -100, 100}, "LHEWeight_originalXWGTUP", "one", "");
    }*/
   // add1DHist({"hgenEventSumw","Sum of gen Weights",1001,-8e+09,8e+09},"one","genEventSumw","");
    //====================================================================================================//
    //}
	
    add1DHist( {"hnevents", "Number of Events", 2, -0.5, 1.5}, "one", "evWeight", "");
	add1DHist( {"hnevents_no_weight", "Number of Events w/o", 2, -0.5, 1.5}, "one", "one", "");
   
    // add1DHist( {"hNgoodElectrons", "NumberofGoodElectrons", 5, 0.0, 5.0}, "NgoodElectrons", "evWeight", "");
    add1DHist( {"hNtightElectrons", "NumberofTightElectrons", 5, 0.0, 5.0}, "NtightElectrons", "evWeight", "");
    
    // add1DHist( {"hNgoodMuons", "# of good Muons ", 5, 0.0, 5.0}, "NgoodMuons", "evWeight", "");
    add1DHist( {"hNtightMuons", "# of tight Muons ", 5, 0.0, 5.0}, "NtightMuons", "evWeight", "");
    
    add1DHist( {"hgood_jetpt_with weight", "Good Jet pt with weight " , 100, 0, 1000} , "goodJets_pt", "evWeight", "");
	add1DHist( {"hgood_jetpt_NOWeight", "Good Jet pt no weihght " , 100, 0, 1000} , "goodJets_pt", "one", "");

    add1DHist( {"hgood_jet1pt", "Good Jet_1 pt with weight " , 100, 0, 2500} , "good_jet1pt", "evWeight", "");
    add1DHist( {"hselected_jet1pt", "SelectedJet_1 pt no weight" , 100, 0, 1000} , "Selected_jet1pt", "evWeight", "");
    add1DHist( {"hselected_jetptWithweight", "clean-Jets with weight" , 100, 0, 2500} , "Selected_jetpt", "evWeight", "");
	add1DHist( {"hselected_jetptNoweight", "clean-Jets w/o weight" , 100, 0, 2500} , "Selected_jetpt", "one", "");

	//add2DHist( {"btagscalef", "btvcent_sf vs seljet_pt" , 100, 0, 500, 100, 0, 500} ,  "Selected_jetpt","btag_SF_case1", "one","");

}
void TopSemiLeptAnalyzer::setTree(TTree *t, std::string outfilename)
{
	if (debug){
        std::cout<< "================================//=================================" << std::endl;
        std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout<< "================================//=================================" << std::endl;
    }

	_rd = ROOT::RDataFrame(*t);
	_rlm = RNode(_rd);
	_outfilename = outfilename;
	_hist1dinfovector.clear();
	_th1dhistos.clear();
	_hist2dinfovector.clear();
	_th2dhistos.clear();
	_varstostore.clear();
	_selections.clear();

	this->setupAnalysis();
}
//================================Selected Object Definitions====================================//

void TopSemiLeptAnalyzer::setupObjects()
{
	// Object selection will be defined in sequence.
	// Selected objects will be stored in new vectors.
	selectElectrons();
	selectMuons();
	selectJets();
	removeOverlaps();
	if(!_isData){
	  this->calculateEvWeight(); // PU, genweight and BTV and Mu and Ele
	}
	selectMET();

}

void TopSemiLeptAnalyzer::setupAnalysis()
{
	if (debug){
        std::cout<< "================================//=================================" << std::endl;
        std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout<< "================================//=================================" << std::endl;
    }
	
 	cout<<"year===="<< _year<< "==runtype=== " <<  _runtype <<endl;

    //==========================================event/gen/ weights==========================================//
    // Event weight for data it's always one. For MC, it depends on the sign
    //=====================================================================================================//
   
	_rlm = _rlm.Define("one", "1.0");
	
	if (_isData && !isDefined("evWeight"))
	{
		_rlm = _rlm.Define("evWeight", [](){
				return 1.0;
			}, {} );
	}
    if(!_isData ) // Only use genWeight
    {
        //_rlm = _rlm.Define("evWeight", "genWeight"); 
       //std::cout<<"Using evWeight = genWeight"<<std::endl;
        
        // auto sumgenweight = _rd.Sum("Generator_weight");
        auto sumgenweight = _rd.Sum("genWeight");
        string sumofgenweight = Form("%f",*sumgenweight);
        _rlm = _rlm.Define("genEventSumw",sumofgenweight.c_str());
        std::cout<<"Sum of genWeights = "<<sumofgenweight.c_str()<<std::endl;
	}
   
	defineCuts();
	defineMoreVars();
	bookHists();
	setupCuts_and_Hists();
	setupTree();
}

