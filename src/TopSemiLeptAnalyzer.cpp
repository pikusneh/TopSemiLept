/*
 * TopSemiLeptAnalyzer.cpp
 *
 *  Created on: May 6, 2022
 *      Author: suyong
 *      Developper: cdozen
 */

#include "Math/GenVector/VectorUtil.h"
#include "TopSemiLeptAnalyzer.h"
#include "overlapRemoval.h"
#include "utility.h"
#include <fstream>
#include "correction.h"
using correction::CorrectionSet;

// TopSemiLeptAnalyzer::TopSemiLeptAnalyzer(TTree *t, std::string outfilename

TopSemiLeptAnalyzer::TopSemiLeptAnalyzer(TTree *tree, std::string outFileName, std::string sampleName)
    : NanoAODAnalyzerrdframe(tree, outFileName), sample_name(sampleName) // Initialize base class and sample_name
{
    HLT2017Names = {"HLT_IsoMu24", "HLT_IsoMu24_eta2p1", "HLT_IsoMu27", "HLT_Mu50", "HLT_OldMu100", "HLT_TkMu100", "HLT_Ele32_WPTight_Gsf_L1DoubleEG", "HLT_Ele32_WPTight_Gsf", "HLT_Ele35_WPTight_Gsf", "HLT_Ele115_CaloIdVT_GsfTrkIdT"};
}
void TopSemiLeptAnalyzer::setSampleName(const std::string &sampleName)
{
    sample_name = sampleName;
}
// Define your cuts here
void TopSemiLeptAnalyzer::defineCuts()
{
    if (debug)
    {
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

void TopSemiLeptAnalyzer::selectChannel()
{
    if (debug)
    {
        std::cout << std::endl;
        std::cout << "================================//=================================" << std::endl;
        std::cout << "Line : " << __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout << "================================//=================================" << std::endl;
    }

    _rlm = _rlm.Define("muonChannel", "(NtightMuons == 1) && (NvetoMuons ==1) ? 1 : 0");
    _rlm = _rlm.Define("electronChannel", "(NtightElectrons == 1) && (NvetoElectrons ==1) ? 1 : 0");
}

void TopSemiLeptAnalyzer::selectElectrons()
{
    cout << "select good electrons" << endl;
    if (debug)
    {
        std::cout << "================================//=================================" << std::endl;
        std::cout << "Line : " << __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout << "================================//=================================" << std::endl;
    }
    // _rlm = _rlm.Define("ElectronSC","abs(Electron_eta+Electron_deltaEtaSC)<1.442 || abs(Electron_eta+Electron_deltaEtaSC)>1.566");
    _rlm = _rlm.Define("ElectronSC", [](const ROOT::VecOps::RVec<float> &eta, const ROOT::VecOps::RVec<float> &deltaEtaSC)
                       {
        ROOT::VecOps::RVec<float> sc(eta.size());
        for (size_t i = 0; i < eta.size(); ++i) {
            sc[i] = std::abs(eta[i] + deltaEtaSC[i]);
        }
        return sc; }, {"Electron_eta", "Electron_deltaEtaSC"});

    // Define a condition to select electrons based on the supercluster eta
    auto scCondition = [](const ROOT::VecOps::RVec<float> &sc)
    {
        ROOT::VecOps::RVec<bool> passCondition(sc.size(), false);
        for (size_t i = 0; i < sc.size(); ++i)
        {
            passCondition[i] = sc[i] < 1.442 || sc[i] > 1.566;
        }
        return passCondition;
    };

    _rlm = _rlm.Define("ElectronSCCondition", scCondition, {"ElectronSC"});

    // Define ElectronsD0DzCut based on Dxy and Dz cuts for barrel and endcap
    auto d0dzCut = [](const ROOT::VecOps::RVec<float> &ElectronSC, const ROOT::VecOps::RVec<float> &Electron_dxy, const ROOT::VecOps::RVec<float> &Electron_dz)
    {
        ROOT::VecOps::RVec<bool> passCuts(ElectronSC.size(), false);
        for (size_t i = 0; i < ElectronSC.size(); ++i)
        {
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

    // Debugging: Check if tightElectrons_4vecs is correctly defined
    auto col_names = _rlm.GetColumnNames();
    if (std::find(col_names.begin(), col_names.end(), "tightElectron_4Vecs") == col_names.end())
    {
        throw std::runtime_error("tightElectrons_4vecs column is not defined correctly!");
    }
    else
    {
        std::cout << "tightElectrons_4vecs column successfully defined." << std::endl;
    }

    // Veto electrons definition
    _rlm = _rlm.Define("vetoElectronsID", ElectronID(1))
               .Define("vetoElectrons", " Electron_pt>15.0 && abs(Electron_eta)<2.4 && vetoElectronsID && ElectronsD0DzCut ")
               .Define("vetoElectrons_pt", "Electron_pt[vetoElectrons]")
               .Define("vetoElectrons_eta", "Electron_eta[vetoElectrons]")
               .Define("vetoElectrons_phi", "Electron_phi[vetoElectrons]")
               .Define("vetoElectrons_mass", "Electron_mass[vetoElectrons]")
               .Define("NvetoElectrons", "int(vetoElectrons_pt.size())")
               .Define("vetoElectrons_4Vecs", ::generate_4vec, {"vetoElectrons_pt", "vetoElectrons_eta", "vetoElectrons_phi", "vetoElectrons_mass"});

    _rlm = _rlm.Define("goodElectronsID", ElectronID(2)); // without pt-eta cuts
    _rlm = _rlm.Define("goodElectrons", "goodElectronsID && Electron_pt>30.0 && abs(Electron_eta)<2.4 && Electron_pfRelIso03_all<0.15");
    _rlm = _rlm.Define("goodElectrons_pt", "Electron_pt[goodElectrons]")
               .Define("goodElectrons_eta", "Electron_eta[goodElectrons]")
               .Define("goodElectrons_phi", "Electron_phi[goodElectrons]")
               .Define("goodElectrons_mass", "Electron_mass[goodElectrons]")
               .Define("goodElectrons_idx", ::good_idx, {"goodElectrons"})
               .Define("NgoodElectrons", "int(goodElectrons_pt.size())");
    _rlm = _rlm.Define("goodElectron_4Vecs", ::generate_4vec, {"goodElectrons_pt", "goodElectrons_eta", "goodElectrons_phi", "goodElectrons_mass"});
}

void TopSemiLeptAnalyzer::selectPhotons()
{
    cout << "Select good photons" << endl;
    // Define Good Photon Selection
    _rlm = _rlm.Define("goodPhotonsID", PhotonID(2)); // Medium ID for good photons
    _rlm = _rlm.Define("goodPhotons", "goodPhotonsID && Photon_pt > 20.0 && abs(Photon_eta) <= 1.4442 && Photon_pixelSeed == 0");

    _rlm = _rlm.Define("goodPhotons_pt", "Photon_pt[goodPhotons]")
               .Define("goodPhotons_eta", "Photon_eta[goodPhotons]")
               .Define("goodPhotons_phi", "Photon_phi[goodPhotons]")
               .Define("goodPhotons_mass", "Photon_mass[goodPhotons]")
               .Define("goodPhotons_charge", "Photon_charge[goodPhotons]")
               .Define("goodPhotons_genPartIdx", "Photon_genPartIdx[goodPhotons]")
               .Define("goodPhotons_idx", ::good_idx, {"goodPhotons"})
               .Define("NgoodPhotons", "int(goodPhotons_pt.size())")
               .Define("goodPhotons_4vecs", ::generate_4vec, {"goodPhotons_pt", "goodPhotons_eta", "goodPhotons_phi", "goodPhotons_mass"});
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
    _rlm = _rlm.Define("goodMuonsID", MuonID(2)); // loose muons
    _rlm = _rlm.Define("goodMuons", "goodMuonsID && Muon_pt > 30 && abs(Muon_eta) < 2.4 && Muon_miniPFRelIso_all < 0.40");
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
// check the twiki page :    https://twiki.cern.ch/twiki/bin/view/CMS/JetID
// to find jetId working points for the purpose of  your analysis.
// jetId==2 means: pass tight ID, fail tightLepVeto
// jetId==6 means: pass tight ID and tightLepVeto ID.
//=============================================================================================//
void TopSemiLeptAnalyzer::selectJets()
{
    cout << "select good jets" << endl;
    // Check if the Jet_hadronFlavour branch exists
    if (_atree->GetBranch("Jet_hadronFlavour") == nullptr)
    {
        std::cout << "Jet_hadronFlavour branch is not found in the input file!!" << std::endl;
    }
    else
    {
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
    if (_atree->GetBranch("Jet_hadronFlavour") != nullptr)
    {
        _rlm = _rlm.Define("goodJets_hadflav", "Jet_hadronFlavour[goodJets]");
    }

    _rlm = _rlm.Define("goodJets_btag", "Jet_btagDeepB[goodJets]") // JetDeepCSV
               .Define("NgoodJets", "int(goodJets_pt.size())")
               .Define("goodJets_4vecs", ::generate_4vec, {"goodJets_pt", "goodJets_eta", "goodJets_phi", "goodJets_mass"});

    _rlm = _rlm.Define("btagcuts", "goodJets_btag>0.4506") // medium wp for 2017
               .Define("good_bjetpt", "goodJets_pt[btagcuts]")
               .Define("good_bjeteta", "goodJets_eta[btagcuts]")
               .Define("good_bjetphi", "goodJets_phi[btagcuts]")
               .Define("good_bjetmass", "goodJets_mass[btagcuts]")
               .Define("good_bjetdeepcsvjet", "goodJets_btag[btagcuts]");

    if (_atree->GetBranch("Jet_hadronFlavour") != nullptr)
    {
        _rlm = _rlm.Define("good_bjethadflav", "goodJets_hadflav[btagcuts]");
    }

    _rlm = _rlm.Define("Ngood_bjets", "int(good_bjetpt.size())")
               .Define("good_bjet4vecs", ::generate_4vec, {"good_bjetpt", "good_bjeteta", "good_bjetphi", "good_bjetmass"});
}


void TopSemiLeptAnalyzer::removeOverlaps()
{

    cout << "Checking overlaps between jets, muons, electrons, and photons" << endl;

    // Lambda function for checking overlapped jets with leptons (muons or electrons)
    auto checkJetLeptonOverlap = [](const FourVectorVec &goodjets, const FourVectorVec &goodlep) {
        // cout << "Inside checkJetLeptonOverlap" << endl;
        ROOT::VecOps::RVec<int> overlapFlags(goodjets.size(), 1);
        for (size_t i = 0; i < goodjets.size(); ++i) {
            auto ajet = goodjets[i];
            auto mindr = 6.0;
            for (size_t j = 0; j < goodlep.size(); ++j) {
                auto alepton = goodlep[j];
                auto dr = ROOT::Math::VectorUtil::DeltaR(ajet, alepton);
                // cout << "  dr between jet " << i << " and lepton " << j << ": " << dr << endl;
                if (dr < mindr) mindr = dr;
            }
            overlapFlags[i] = mindr > 0.4 ? 1 : 0;
            // cout << "  mindr for jet " << i << ": " << mindr << " -> " << overlapFlags[i] << endl;
        }
        return overlapFlags;
    };

    // // Lambda function for checking overlapped photons with leptons (muons or electrons)
    // auto checkPhotonLeptonOverlap = [](FourVectorVec &goodphotons, FourVectorVec &goodlep)
    // {
    //     cout << "Inside checkPhotonLeptonOverlap" << endl;
    //     doubles mindrlepton;
    //     for (size_t i = 0; i < goodphotons.size(); ++i)
    //     {
    //         auto aphoton = goodphotons[i];
    //         auto mindr = 6.0;
    //         for (size_t j = 0; j < goodlep.size(); ++j)
    //         {
    //             auto alepton = goodlep[j];
    //             auto dr = ROOT::Math::VectorUtil::DeltaR(aphoton, alepton);
    //             cout << "  dr between photon " << i << " and lepton " << j << ": " << dr << endl;
    //             if (dr < mindr)
    //                 mindr = dr;
    //         }
    //         int out = mindr > 0.4 ? 1 : 0;
    //         mindrlepton.emplace_back(out);
    //         cout << "  mindr for photon " << i << ": " << mindr << " -> " << out << endl;
    //     }
    //     return mindrlepton;
    // };

    // // Lambda function for checking overlapped jets with photons
    // auto checkJetPhotonOverlap = [](FourVectorVec &goodjets, FourVectorVec &goodphotons)
    // {
    //     cout << "Inside checkJetPhotonOverlap" << endl;
    //     doubles mindrphoton;
    //     for (size_t i = 0; i < goodjets.size(); ++i)
    //     {
    //         auto ajet = goodjets[i];
    //         auto mindr = 6.0;
    //         for (size_t j = 0; j < goodphotons.size(); ++j)
    //         {
    //             auto aphoton = goodphotons[j];
    //             auto dr = ROOT::Math::VectorUtil::DeltaR(ajet, aphoton);
    //             cout << "  dr between jet " << i << " and photon " << j << ": " << dr << endl;
    //             if (dr < mindr)
    //                 mindr = dr;
    //         }
    //         int out = mindr > 0.1 ? 1 : 0;
    //         mindrphoton.emplace_back(out);
    //         cout << "  mindr for jet " << i << ": " << mindr << " -> " << out << endl;
    //     }
    //     return mindrphoton;
    // };

    cout << "Defining muonjetoverlap" << endl;
    _rlm = _rlm.Define("muonjetoverlap", checkJetLeptonOverlap, {"goodJets_4vecs", "tightMuons_4vecs"});

    cout << "Defining electronjetoverlap" << endl;
    _rlm = _rlm.Define("electronjetoverlap", checkJetLeptonOverlap, {"goodJets_4vecs", "tightElectron_4Vecs"});

    cout << "Defining jetNoOverlapWithLeptons" << endl;
    _rlm = _rlm.Define("jetNoOverlapWithLeptons", "muonjetoverlap && electronjetoverlap");

    cout << "Defining cleanedJetsWithLeptons" << endl;
    _rlm = _rlm.Define("cleanedJetsWithLeptons", [](const FourVectorVec &goodjets, const ROOT::VecOps::RVec<int> &overlapFlags) {
        FourVectorVec cleanedJets;
        for (size_t i = 0; i < goodjets.size(); ++i) {
            if (overlapFlags[i]) {
                cleanedJets.push_back(goodjets[i]);
            }
        }
        return cleanedJets;
    }, {"goodJets_4vecs", "jetNoOverlapWithLeptons"});

    // cout << "Defining photonjetoverlap" << endl;
    // _rlm = _rlm.Define("photonjetoverlap", checkJetPhotonOverlap, {"goodJets_4vecs", "goodPhotons_4vecs"});

    // Define overlap removal for jets and muons, jets and electrons, and jets and photons
    // _rlm = _rlm.Define("muonjetoverlap", checkJetLeptonOverlap, {"goodJets_4vecs", "tightMuons_4vecs"})
    //            .Define("electronjetoverlap", checkJetLeptonOverlap, {"goodJets_4vecs", "tightElectron_4Vecs"})
    //            .Define("photonjetoverlap", checkJetPhotonOverlap, {"goodJets_4vecs", "goodPhotons_4vecs"});

    // Clean jets by removing overlaps with muons, electrons, and photons
    // _rlm = _rlm.Define("jetNoOverlapWithLeptons", "muonjetoverlap && electronjetoverlap")
    //            .Define("cleanedJetsWithLeptons", "goodJets_4vecs[jetNoOverlapWithLeptons]")
    //            .Define("finalCleanedJets", "cleanedJetsWithLeptons[photonjetoverlap]");

    // cout << "Defining jetNoOverlapWithLeptons" << endl;
    // _rlm = _rlm.Define("jetNoOverlapWithLeptons", "muonjetoverlap && electronjetoverlap");

    // cout << "Defining cleanedJetsWithLeptons" << endl;
    // _rlm = _rlm.Define("cleanedJetsWithLeptons", "goodJets_4vecs[jetNoOverlapWithLeptons]");

    // cout << "Defining photonJetOverlap for final cleaned jets" << endl;
    // _rlm = _rlm.Define("photonJetOverlapWithCleanedJets", checkJetPhotonOverlap, {"cleanedJetsWithLeptons", "goodPhotons_4vecs"});

    // cout << "Defining finalCleanedJets" << endl;
    // _rlm = _rlm.Define("finalCleanedJets", "cleanedJetsWithLeptons[photonJetOverlapWithCleanedJets]");

    // // Define cleaned jet properties
    // cout << "Defining Selected_jetpt" << endl;
    // _rlm = _rlm.Define("Selected_jetpt", "goodJets_pt[jetNoOverlapWithLeptons]");

    // Define cleaned jet properties
    // _rlm = _rlm.Define("Selected_jetpt", "goodJets_pt[jetNoOverlapWithLeptons && photonjetoverlap]")
    //            .Define("Selected_jeteta", "goodJets_eta[jetNoOverlapWithLeptons && photonjetoverlap]")
    //            .Define("Selected_jetphi", "goodJets_phi[jetNoOverlapWithLeptons && photonjetoverlap]")
    //            .Define("Selected_jetmass", "goodJets_mass[jetNoOverlapWithLeptons && photonjetoverlap]")
    //            .Define("Selected_jetbtag", "goodJets_btag[jetNoOverlapWithLeptons && photonjetoverlap]")
    //            .Define("ncleanjetspass", "int(Selected_jetpt.size())")
    //            .Define("cleanjet4vecs", ::generate_4vec, {"Selected_jetpt", "Selected_jeteta", "Selected_jetphi", "Selected_jetmass"})
    //            .Define("Selected_jetHT", "Sum(Selected_jetpt)");

    // cout << "Defining other jet properties" << endl;
    // _rlm = _rlm.Define("Selected_jeteta", "goodJets_eta[jetNoOverlapWithLeptons]")
    //            .Define("Selected_jetphi", "goodJets_phi[jetNoOverlapWithLeptons]")
    //            .Define("Selected_jetmass", "goodJets_mass[jetNoOverlapWithLeptons]")
    //            .Define("Selected_jetbtag", "goodJets_btag[jetNoOverlapWithLeptons]")
    //            .Define("ncleanjetspass", "int(Selected_jetpt.size())")
    //            .Define("cleanjet4vecs", ::generate_4vec, {"Selected_jetpt", "Selected_jeteta", "Selected_jetphi", "Selected_jetmass"})
    //            .Define("Selected_jetHT", "Sum(Selected_jetpt)");

    // bool hasJetHadronFlavour = (_atree->GetBranch("Jet_hadronFlavour") != nullptr);
    // if (hasJetHadronFlavour)
    // {
    //     _rlm = _rlm.Define("Selected_jethadflav", "goodJets_hadflav[jetNoOverlapWithLeptons]");
    // }

    // // Clean b-jets after removing overlaps
    // _rlm = _rlm.Define("btagcuts2", "Selected_jetbtag > 0.4506") // medium wp
    //            .Define("Selected_bjetpt", "Selected_jetpt[btagcuts2]")
    //            .Define("Selected_bjeteta", "Selected_jeteta[btagcuts2]")
    //            .Define("Selected_bjetphi", "Selected_jetphi[btagcuts2]")
    //            .Define("Selected_bjetmass", "Selected_jetmass[btagcuts2]")
    //            .Define("ncleanbjetspass", "int(Selected_bjetpt.size())")
    //            .Define("Selected_bjetHT", "Sum(Selected_bjetpt)")
    //            .Define("cleanbjet4vecs", ::generate_4vec, {"Selected_bjetpt", "Selected_bjeteta", "Selected_bjetphi", "Selected_bjetmass"});

    // if (hasJetHadronFlavour)
    // {
    //     _rlm = _rlm.Define("Selected_bjethadflav", "Selected_jethadflav[btagcuts2]");
    // }

    // // Apply overlap removal to photons
    // _rlm = _rlm.Define("leptonPhotonOverlap", checkPhotonLeptonOverlap, {"goodPhotons_4vecs", "tightLeptons_4vecs"})
    //            .Define("cleanedPhotons", "goodPhotons_4vecs[leptonPhotonOverlap]");

    cout << "Defining Selected_jetpt" << endl;
    _rlm = _rlm.Define("Selected_jetpt", "goodJets_pt[jetNoOverlapWithLeptons]");

    cout << "Defining other jet properties" << endl;
    _rlm = _rlm.Define("Selected_jeteta", "goodJets_eta[jetNoOverlapWithLeptons]")
               .Define("Selected_jetphi", "goodJets_phi[jetNoOverlapWithLeptons]")
               .Define("Selected_jetmass", "goodJets_mass[jetNoOverlapWithLeptons]")
               .Define("Selected_jetbtag", "goodJets_btag[jetNoOverlapWithLeptons]")
               .Define("ncleanjetspass", "int(Selected_jetpt.size())")
               .Define("cleanjet4vecs", ::generate_4vec, {"Selected_jetpt", "Selected_jeteta", "Selected_jetphi", "Selected_jetmass"})
               .Define("Selected_jetHT", "Sum(Selected_jetpt)");

    bool hasJetHadronFlavour = (_atree->GetBranch("Jet_hadronFlavour") != nullptr);
    if (hasJetHadronFlavour)
    {
        _rlm = _rlm.Define("Selected_jethadflav", "goodJets_hadflav[jetNoOverlapWithLeptons]");
    }

    // Clean b-jets after removing overlaps
    _rlm = _rlm.Define("btagcuts2", "Selected_jetbtag > 0.4506") // medium wp
               .Define("Selected_bjetpt", "Selected_jetpt[btagcuts2]")
               .Define("Selected_bjeteta", "Selected_jeteta[btagcuts2]")
               .Define("Selected_bjetphi", "Selected_jetphi[btagcuts2]")
               .Define("Selected_bjetmass", "Selected_jetmass[btagcuts2]")
               .Define("ncleanbjetspass", "int(Selected_bjetpt.size())")
               .Define("Selected_bjetHT", "Sum(Selected_bjetpt)")
               .Define("cleanbjet4vecs", ::generate_4vec, {"Selected_bjetpt", "Selected_bjeteta", "Selected_bjetphi", "Selected_bjetmass"});

    if (hasJetHadronFlavour)
    {
        _rlm = _rlm.Define("Selected_bjethadflav", "Selected_jethadflav[btagcuts2]");
    }
}

ROOT::RDF::RNode TopSemiLeptAnalyzer::applyOverlapRemoval(ROOT::RDF::RNode df, const std::string &sample_name)
{
    bool verbose = false;
    auto initial_count = df.Count();

    if (sample_name == "TTbar_Hadronic" || sample_name == "TTbar_Semilept" || sample_name == "TTbar_Dilept")
    {
        df = df.Filter([verbose, sample_name](const ROOT::RVec<float> &genPt, const ROOT::RVec<float> &genEta,
                                              const ROOT::RVec<float> &genPhi, const ROOT::RVec<int> &genPdgId,
                                              const ROOT::RVec<int> &genStatus, const ROOT::RVec<int> &genPartIdxMother)
                       { return overlapRemoval(genPt, genEta, genPhi, genPdgId, genStatus, genPartIdxMother, 10.0, 5.0, 0.1, verbose, sample_name); },
                       {"GenPart_pt", "GenPart_eta", "GenPart_phi", "GenPart_pdgId", "GenPart_status", "GenPart_genPartIdxMother"});
    }
    else if (sample_name == "WJets" || sample_name == "DYJets" || sample_name == "ST_t-channel")
    {
        df = df.Filter([verbose, sample_name](const ROOT::RVec<float> &genPt, const ROOT::RVec<float> &genEta,
                                              const ROOT::RVec<float> &genPhi, const ROOT::RVec<int> &genPdgId,
                                              const ROOT::RVec<int> &genStatus, const ROOT::RVec<int> &genPartIdxMother)
                       { return overlapRemoval(genPt, genEta, genPhi, genPdgId, genStatus, genPartIdxMother, 15.0, 2.6, 0.05, verbose, sample_name); },
                       {"GenPart_pt", "GenPart_eta", "GenPart_phi", "GenPart_pdgId", "GenPart_status", "GenPart_genPartIdxMother"});
    }

    auto final_count = df.Count();

    auto removed_count = initial_count.GetValue() - final_count.GetValue();
    std::cout << "Sample: " << sample_name << std::endl;
    std::cout << "Initial number of events: " << initial_count.GetValue() << std::endl;
    std::cout << "Final number of events: " << final_count.GetValue() << std::endl;
    std::cout << "Number of overlapped events removed: " << removed_count << std::endl;

    return df;
}

void TopSemiLeptAnalyzer::GenParticle4vec()
{
    _rlm = _rlm.Define("GenPartpt", "GenPart_pt")
               .Define("GenParteta", "GenPart_eta")
               .Define("GenPartphi", "GenPart_phi")
               .Define("GenPartmass", "GenPart_mass")
               .Define("GenPartpdgId", "GenPart_pdgId");

    _rlm = _rlm.Define("genParticles_4vecs", [](const ROOT::VecOps::RVec<float> &gen_pt, const ROOT::VecOps::RVec<float> &gen_eta, const ROOT::VecOps::RVec<float> &gen_phi, const ROOT::VecOps::RVec<float> &gen_mass)
                       {
                    ROOT::VecOps::RVec<ROOT::Math::PtEtaPhiMVector> vecs;
                    for (size_t i = 0; i < gen_pt.size(); ++i) {
                        vecs.emplace_back(gen_pt[i], gen_eta[i], gen_phi[i], gen_mass[i]);
                    }
                    return vecs; }, {"GenPart_pt", "GenPart_eta", "GenPart_phi", "GenPart_mass"});
}
// Photon Categorization
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ROOT::RDF::RNode TopSemiLeptAnalyzer::categorizePhotons(ROOT::RDF::RNode df)
{
    return df.Define("_phoGenMatchInd", [this](const ROOT::RVec<int> &phoGenPartIdx)
                     { return phoGenPartIdx; }, {"goodPhotons_genPartIdx"})

        .Define("_photonIsGenuine", [this](const ROOT::RVec<int> &phoGenPartIdx, const ROOT::RVec<float> &phoEta, const ROOT::RVec<float> &phoPhi, const ROOT::RVec<int> &genPartPdgId, const ROOT::RVec<float> &genPartPt, const ROOT::RVec<float> &genPartEta, const ROOT::RVec<float> &genPartPhi, const ROOT::RVec<int> &genPartIdxMother, const ROOT::VecOps::RVec<ROOT::Math::PtEtaPhiMVector> &genParticles_4vecs, const ROOT::VecOps::RVec<ROOT::Math::PtEtaPhiMVector> &goodPhotons_4vecs)
                {
        std::vector<bool> genuineFlags;
        for (size_t i = 0; i < phoGenPartIdx.size(); ++i) {
            bool isGenuine, isMisIDEle, isHadronicPhoton, isHadronicFake, isPUPhoton;
            categorizeSinglePhoton(i, phoGenPartIdx, phoEta, phoPhi, genPartPdgId, genPartPt, genPartEta, genPartPhi, genPartIdxMother,
                                genParticles_4vecs, goodPhotons_4vecs, isGenuine, isMisIDEle, isHadronicPhoton, isHadronicFake, isPUPhoton);
            genuineFlags.push_back(isGenuine);
        }
        return genuineFlags; }, {"goodPhotons_genPartIdx", "goodPhotons_eta", "goodPhotons_phi", "GenPart_pdgId", "GenPart_pt", "GenPart_eta", "GenPart_phi", "GenPart_genPartIdxMother", "genParticles_4vecs", "goodPhotons_4vecs"})

        .Define("_photonIsMisIDEle", [this](const ROOT::RVec<int> &phoGenPartIdx, const ROOT::RVec<float> &phoEta, const ROOT::RVec<float> &phoPhi, const ROOT::RVec<int> &genPartPdgId, const ROOT::RVec<float> &genPartPt, const ROOT::RVec<float> &genPartEta, const ROOT::RVec<float> &genPartPhi, const ROOT::RVec<int> &genPartIdxMother, const ROOT::VecOps::RVec<ROOT::Math::PtEtaPhiMVector> &genParticles_4vecs, const ROOT::VecOps::RVec<ROOT::Math::PtEtaPhiMVector> &goodPhotons_4vecs)
                {
        std::vector<bool> misIDeleFlags;
        for (size_t i = 0; i < phoGenPartIdx.size(); ++i) {
            bool isGenuine, isMisIDEle, isHadronicPhoton, isHadronicFake, isPUPhoton;
            categorizeSinglePhoton(i, phoGenPartIdx, phoEta, phoPhi, genPartPdgId, genPartPt, genPartEta, genPartPhi, genPartIdxMother,
                                genParticles_4vecs, goodPhotons_4vecs, isGenuine, isMisIDEle, isHadronicPhoton, isHadronicFake, isPUPhoton);
            misIDeleFlags.push_back(isMisIDEle);
        }
        return misIDeleFlags; }, {"goodPhotons_genPartIdx", "goodPhotons_eta", "goodPhotons_phi", "GenPart_pdgId", "GenPart_pt", "GenPart_eta", "GenPart_phi", "GenPart_genPartIdxMother", "genParticles_4vecs", "goodPhotons_4vecs"})

        .Define("_photonIsHadronicPhoton", [this](const ROOT::RVec<int> &phoGenPartIdx, const ROOT::RVec<float> &phoEta, const ROOT::RVec<float> &phoPhi, const ROOT::RVec<int> &genPartPdgId, const ROOT::RVec<float> &genPartPt, const ROOT::RVec<float> &genPartEta, const ROOT::RVec<float> &genPartPhi, const ROOT::RVec<int> &genPartIdxMother, const ROOT::VecOps::RVec<ROOT::Math::PtEtaPhiMVector> &genParticles_4vecs, const ROOT::VecOps::RVec<ROOT::Math::PtEtaPhiMVector> &goodPhotons_4vecs)
                {
        std::vector<bool> hadronicPhotonFlags;
        for (size_t i = 0; i < phoGenPartIdx.size(); ++i) {
            bool isGenuine, isMisIDEle, isHadronicPhoton, isHadronicFake, isPUPhoton;
            categorizeSinglePhoton(i, phoGenPartIdx, phoEta, phoPhi, genPartPdgId, genPartPt, genPartEta, genPartPhi, genPartIdxMother,
                                genParticles_4vecs, goodPhotons_4vecs, isGenuine, isMisIDEle, isHadronicPhoton, isHadronicFake, isPUPhoton);
            hadronicPhotonFlags.push_back(isHadronicPhoton);
        }
        return hadronicPhotonFlags; }, {"goodPhotons_genPartIdx", "goodPhotons_eta", "goodPhotons_phi", "GenPart_pdgId", "GenPart_pt", "GenPart_eta", "GenPart_phi", "GenPart_genPartIdxMother", "genParticles_4vecs", "goodPhotons_4vecs"})

        .Define("_photonIsHadronicFake", [this](const ROOT::RVec<int> &phoGenPartIdx, const ROOT::RVec<float> &phoEta, const ROOT::RVec<float> &phoPhi, const ROOT::RVec<int> &genPartPdgId, const ROOT::RVec<float> &genPartPt, const ROOT::RVec<float> &genPartEta, const ROOT::RVec<float> &genPartPhi, const ROOT::RVec<int> &genPartIdxMother, const ROOT::VecOps::RVec<ROOT::Math::PtEtaPhiMVector> &genParticles_4vecs, const ROOT::VecOps::RVec<ROOT::Math::PtEtaPhiMVector> &goodPhotons_4vecs)
                {
        std::vector<bool> hadronicFakeFlags;
        for (size_t i = 0; i < phoGenPartIdx.size(); ++i) {
            bool isGenuine, isMisIDEle, isHadronicPhoton, isHadronicFake, isPUPhoton;
            categorizeSinglePhoton(i, phoGenPartIdx, phoEta, phoPhi, genPartPdgId, genPartPt, genPartEta, genPartPhi, genPartIdxMother,
                                genParticles_4vecs, goodPhotons_4vecs, isGenuine, isMisIDEle, isHadronicPhoton, isHadronicFake, isPUPhoton);
            hadronicFakeFlags.push_back(isHadronicFake || isPUPhoton);
        }
        return hadronicFakeFlags; }, {"goodPhotons_genPartIdx", "goodPhotons_eta", "goodPhotons_phi", "GenPart_pdgId", "GenPart_pt", "GenPart_eta", "GenPart_phi", "GenPart_genPartIdxMother", "genParticles_4vecs", "goodPhotons_4vecs"});
}

void TopSemiLeptAnalyzer::categorizeSinglePhoton(int phoInd, const ROOT::RVec<int> &phoGenPartIdx, const ROOT::RVec<float> &phoEta, const ROOT::RVec<float> &phoPhi,
                                                 const ROOT::RVec<int> &genPartPdgId, const ROOT::RVec<float> &genPartPt, const ROOT::RVec<float> &genPartEta,
                                                 const ROOT::RVec<float> &genPartPhi, const ROOT::RVec<int> &genPartIdxMother,
                                                 const ROOT::VecOps::RVec<ROOT::Math::PtEtaPhiMVector> &genParticles_4vecs,
                                                 const ROOT::VecOps::RVec<ROOT::Math::PtEtaPhiMVector> &goodPhotons_4vecs,
                                                 bool &isGenuine, bool &isMisIDEle, bool &isHadronicPhoton, bool &isHadronicFake, bool &isPUPhoton)
{
    isGenuine = isMisIDEle = isHadronicPhoton = isHadronicFake = isPUPhoton = false;

    int mcMatchInd = phoGenPartIdx[phoInd];

    if (mcMatchInd == -1)
    {
        std::vector<int> genParticleCone_pid;
        std::vector<int> genParticleCone_idx;

        for (size_t genIdx = 0; genIdx < genPartPdgId.size(); ++genIdx)
        {
            if (genPartPt[genIdx] < 5)
                continue;

            std::vector<int> excludedPdgIds = {12, -12, 14, -14, 16, -16};
            int genPID = genPartPdgId[genIdx];
            if (std::find(excludedPdgIds.begin(), excludedPdgIds.end(), genPID) != excludedPdgIds.end())
                continue;

            double dRValue = ROOT::Math::VectorUtil::DeltaR(genParticles_4vecs[genIdx], goodPhotons_4vecs[phoInd]);
            if (dRValue < 0.3)
            {
                genParticleCone_idx.push_back(genIdx);
                genParticleCone_pid.push_back(genPID);
            }
        }

        if (genParticleCone_pid.empty())
        {
            isPUPhoton = true;
            return;
        }

        if (std::find(genParticleCone_pid.begin(), genParticleCone_pid.end(), 111) != genParticleCone_pid.end() &&
            std::find(genParticleCone_pid.begin(), genParticleCone_pid.end(), 22) != genParticleCone_pid.end())
        {
            isHadronicPhoton = true;
            return;
        }

        isHadronicFake = true;
        return;
    }

    int mcMatchPDGID = genPartPdgId[mcMatchInd];
    int maxPDGID = 0;
    int parentIdx = mcMatchInd;
    while (parentIdx != -1)
    {
        maxPDGID = std::max(maxPDGID, std::abs(genPartPdgId[parentIdx]));
        parentIdx = genPartIdxMother[parentIdx];
    }

    if (mcMatchPDGID == 22)
    {
        if (maxPDGID < 37)
        {
            isGenuine = true;
        }
        else
        {
            isHadronicPhoton = true;
        }
    }
    else if (std::abs(mcMatchPDGID) == 11)
    {
        isMisIDEle = true;
    }
    else
    {
        isHadronicFake = true;
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void TopSemiLeptAnalyzer::calculateEvWeight()
{

    int _case = 1;
    std::vector<std::string> Jets_vars_names = {"Selected_jethadflav", "Selected_jeteta", "Selected_jetpt"};
    if (_case != 1)
    {
        Jets_vars_names.emplace_back("Selected_jetbtag");
    }
    std::string output_btag_column_name = "btag_SF_";
    _rlm = calculateBTagSF(_rlm, Jets_vars_names, _case, output_btag_column_name);

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

    std::vector<std::string> Photon_vars_names = {"goodPhotons_eta", "goodPhotons_pt"};
    std::string output_pho_column_name = "photon_SF_";
    _rlm = calculatePhoSF(_rlm, Photon_vars_names, output_pho_column_name);

    // Prefiring Weight for 2016 and 2017
      _rlm = applyPrefiringWeight(_rlm);

    // Total event Weight:
    //   _rlm = _rlm.Define("evWeight", " pugenWeight *prefiring_SF_central * btag_SF_bcflav_central * btag_SF_lflav_central * muon_SF_central * ele_SF_central");
    _rlm = _rlm.Define("evWeight", " pugenWeight * prefiring_SF_central * btag_SF_central * muon_SF_central * ele_SF_central");
}
// MET

void TopSemiLeptAnalyzer::selectMET()
{
    if (debug)
    {
        std::cout << "================================//=================================" << std::endl;
        std::cout << "Line : " << __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout << "================================//=================================" << std::endl;
    }

    // _rlm = _rlm.Define("goodMET_sumET","MET_sumEt>800")
    _rlm = _rlm.Define("goodMET_pt", "MET_pt>5");
    //             .Define("goodMET_eta","MET_eta[goodMET]")
    //             .Define("goodMET_phi","MET_phi[goodMET]")
    //             .Define("NgoodMET","int(goodMET_pt.size())");
    // _rlm = _rlm.Define("goodMet", "MET_sumEt>600 && MET_pt>5");
    // _rlm = _rlm.Define("goodMet_pt", "MET_pt[goodMet]");
}

//=============================define variables==================================================//
void TopSemiLeptAnalyzer::defineMoreVars()
{
    if (debug)
    {
        std::cout << "================================//=================================" << std::endl;
        std::cout << "Line : " << __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout << "================================//=================================" << std::endl;
    }

    addVar({"good_muon1pt", "goodMuons_pt[0]", ""});
    addVar({"tight_muon1pt", "tightMuons_pt[0]", ""});

    // selected jet candidates
    addVar({"good_jet1pt", "(goodJets_pt.size()>0) ? goodJets_pt[0] : -1", ""});
    addVar({"Selected_jet1pt", "(Selected_jetpt.size()>0) ? Selected_jetpt[0] : -1", ""});
    addVar({"good_jet1eta", "goodJets_eta[0]", ""});
    addVar({"good_jet1mass", "goodJets_mass[0]", ""});

    // Store these variables in the tree
    addVartoStore("_photonIsGenuine");
    addVartoStore("_photonIsMisIDEle");
    addVartoStore("_photonIsHadronicPhoton");
    addVartoStore("_photonIsHadronicFake");

    //================================Store variables in tree=======================================//
    addVartoStore("run");
    addVartoStore("luminosityBlock");
    addVartoStore("event");
    addVartoStore("evWeight");

    // addVartoStore("genWeight");
    // addVartoStore("genEventSumw");
    addVartoStore("muonChannel");
    addVartoStore("electronChannel");
    // electron
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

    // muon
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

    // photon
    addVartoStore("NgoodPhotons");
    addVartoStore("goodPhotons_pt");
    addVartoStore("goodPhotons_eta");

    // jet
    addVartoStore("nJet");
    addVartoStore("Jet_pt");
    addVartoStore("NgoodJets");
    addVartoStore("goodJets_pt");
    addVartoStore("Selected_jetpt");
    addVartoStore("Selected_jeteta");
    addVartoStore("Selected_jetbtag");

    addVartoStore("good_bjetdeepcsvjet");
    addVartoStore("Ngood_bjets");

    if (_atree->GetBranch("Jet_hadronFlavour") != nullptr)
    {
        addVartoStore("Selected_jethadflav");
        addVartoStore("goodJets_hadflav");
        addVartoStore("good_bjethadflav");
        addVartoStore("Selected_bjethadflav");
    }
    // jetmet corr
    addVartoStore("Jet_pt_corr");
    addVartoStore("Jet_pt_corr_up");
    addVartoStore("Jet_pt_corr_down");
    addVartoStore("Jet_pt_relerror");
    addVartoStore("MET_pt_corr");
    addVartoStore("MET_pt");
    addVartoStore("MET_phi");
    // addVartoStore("Photon_pt");

    if (!_isData)
    {
        // case1 btag correction- fixed wp
        addVartoStore("btag_SF_central");
        // addVartoStore("btag_SF_bcflav_central");
        // addVartoStore("btag_SF_lflav_central");
        // addVartoStore("totbtagSF");
        // addVartoStore("evWeight_wobtagSF");
        addVartoStore("btag_SF_up");
        addVartoStore("btag_SF_down");

        // case3 shape correction
        // addVartoStore("btagWeight_case3");

        // MUONID - ISO SF & WEIGHT
        addVartoStore("muon_SF_central");
        // addVartoStore("muon_id_weight");
        addVartoStore("muon_SF_id_sf");
        addVartoStore("muon_SF_id_syst");
        addVartoStore("muon_SF_id_systup");
        addVartoStore("muon_SF_id_systdown");
        // addVartoStore("muonISO_SF");
        addVartoStore("muon_SF_iso_sf");

        addVartoStore("ele_SF_central");
        addVartoStore("ele_SF_id_sf");
        addVartoStore("ele_SF_id_sfup");
        addVartoStore("ele_SF_id_sfdown");
        addVartoStore("pho_SF_central");
        addVartoStore("pho_SF_id_sf");
        addVartoStore("pho_SF_id_sfup");
        addVartoStore("pho_SF_up");
        addVartoStore("pho_SF_down");
        addVartoStore("pugenWeight");
        addVartoStore("prefiring_SF_central");

        addVartoStore("evWeight");
    }

    if (!_isData)
    { // Only add gen-level information for MC data, gen-level name is changed to avoid conflict
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
    // add1DHist( {"hnevents", "hist_title; x_axis title; y_axis title", 2, -0.5, 1.5}, "one", "evWeight", "");
    // add1DHist( {"hgoodelectron1_pt", "good electron1_pt; #electron p_{T}; Entries / after ", 18, -2.7, 2.7}, "good_electron1pt", "evWeight", "0");
    //======================================================================================================//

    if (debug)
    {
        std::cout << "================================//=================================" << std::endl;
        std::cout << "Line : " << __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout << "================================//=================================" << std::endl;
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

    add1DHist({"hnevents", "Number of Events", 2, -0.5, 1.5}, "one", "evWeight", "");
    add1DHist({"hnevents_no_weight", "Number of Events w/o", 2, -0.5, 1.5}, "one", "one", "");

    // add1DHist( {"hNgoodElectrons", "NumberofGoodElectrons", 5, 0.0, 5.0}, "NgoodElectrons", "evWeight", "");
    add1DHist({"hNtightElectrons", "NumberofTightElectrons", 5, 0.0, 5.0}, "NtightElectrons", "evWeight", "");

    // add1DHist( {"hNgoodMuons", "# of good Muons ", 5, 0.0, 5.0}, "NgoodMuons", "evWeight", "");
    add1DHist({"hNtightMuons", "# of tight Muons ", 5, 0.0, 5.0}, "NtightMuons", "evWeight", "");

    add1DHist({"hgood_jetpt_with weight", "Good Jet pt with weight ", 100, 0, 1000}, "goodJets_pt", "evWeight", "");
    add1DHist({"hgood_jetpt_NOWeight", "Good Jet pt no weihght ", 100, 0, 1000}, "goodJets_pt", "one", "");

    add1DHist({"hgood_jet1pt", "Good Jet_1 pt with weight ", 100, 0, 2500}, "good_jet1pt", "evWeight", "");
    add1DHist({"hselected_jet1pt", "SelectedJet_1 pt no weight", 100, 0, 1000}, "Selected_jet1pt", "evWeight", "");
    add1DHist({"hselected_jetptWithweight", "clean-Jets with weight", 100, 0, 2500}, "Selected_jetpt", "evWeight", "");
    add1DHist({"hselected_jetptNoweight", "clean-Jets w/o weight", 100, 0, 2500}, "Selected_jetpt", "one", "");

    // add2DHist( {"btagscalef", "btvcent_sf vs seljet_pt" , 100, 0, 500, 100, 0, 500} ,  "Selected_jetpt","btag_SF_case1", "one","");
}
void TopSemiLeptAnalyzer::setTree(TTree *t, std::string outfilename)
{
    if (debug)
    {
        std::cout << "================================//=================================" << std::endl;
        std::cout << "Line : " << __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout << "================================//=================================" << std::endl;
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
    // std::string sample_name = "TTbar";

    // Perform overlap removal based on gen-level photons
    if (!_isData)
    {
        _rlm = applyOverlapRemoval(_rlm, sample_name); // Apply overlap removal
    }

    // Continue with the other object selections

    selectElectrons();
    selectMuons();
    selectChannel();
    selectJets();
    GenParticle4vec();
    selectPhotons();
    _rlm = categorizePhotons(_rlm);
    removeOverlaps();
    if (!_isData)
    {
        this->calculateEvWeight(); // PU, genweight and BTV and Mu and Ele
    }
    selectMET();
}

void TopSemiLeptAnalyzer::setupAnalysis()
{
    if (debug)
    {
        std::cout << "================================//=================================" << std::endl;
        std::cout << "Line : " << __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout << "================================//=================================" << std::endl;
    }

    cout << "year====" << _year << "==runtype=== " << _runtype << endl;

    //==========================================event/gen/ weights==========================================//
    // Event weight for data it's always one. For MC, it depends on the sign
    //=====================================================================================================//

    _rlm = _rlm.Define("one", "1.0");

    if (_isData && !isDefined("evWeight"))
    {
        _rlm = _rlm.Define("evWeight", []()
                           { return 1.0; }, {});
    }
    if (!_isData) // Only use genWeight
    {
        //_rlm = _rlm.Define("evWeight", "genWeight");
        // std::cout<<"Using evWeight = genWeight"<<std::endl;

        // auto sumgenweight = _rd.Sum("Generator_weight");
        auto sumgenweight = _rd.Sum("genWeight");
        string sumofgenweight = Form("%f", *sumgenweight);
        _rlm = _rlm.Define("genEventSumw", sumofgenweight.c_str());
        std::cout << "Sum of genWeights = " << sumofgenweight.c_str() << std::endl;
    }

    defineCuts();
    defineMoreVars();
    bookHists();
    setupCuts_and_Hists();
    setupTree();
}
