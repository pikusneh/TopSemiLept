/*
 * SkimEvents.cpp
 *
 *  Created on: Dec 9, 2018
 *      Author: suyong
 */

#include "Math/GenVector/VectorUtil.h"
#include "SkimEvents.h"
#include "utility.h"

// Constructor implementation
SkimEvents::SkimEvents(TTree *t, std::string outfilename)
    : NanoAODAnalyzerrdframe(t, outfilename) {
    setupAnalysis();  // Ensure setupAnalysis is called during construction
}

// Define your cuts here
void SkimEvents::defineCuts() {
    // Print debug information if enabled
    if (debug) {
        std::cout << "================================//=================================" << std::endl;
        std::cout << "Line : " << __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout << "================================//=================================" << std::endl;
    }

    // Display the number of entries before filtering
    auto Nentry = _rlm.Count();
    std::cout << "-------------------------------------------------------------------" << std::endl;
    std::cout << "Usage of ranges:\n"
              << " - All entries: " << *Nentry << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;

    // Apply HLT trigger cuts
    addCuts("HLT_IsoMu24 || HLT_IsoMu24_eta2p1 || HLT_IsoMu27 || HLT_Mu50 || "
            "HLT_OldMu100 || HLT_TkMu100 || HLT_Ele32_WPTight_Gsf_L1DoubleEG || "
            "HLT_Ele32_WPTight_Gsf || HLT_Ele35_WPTight_Gsf || HLT_Ele115_CaloIdVT_GsfTrkIdT || "
            "HLT_Photon200", "0");  // 2017 triggers
}

// Define the variables to store in the output
void SkimEvents::defineMoreVars() {
    if (debug) {
        std::cout << "================================//=================================" << std::endl;
        std::cout << "Line : " << __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout << "================================//=================================" << std::endl;
    }

    // Example of adding variables
    addVar({"Sel_jetHT", "Sum(Sel_jetpt)"});

    // Define variables that you want to store
    addVartoStore("run");
    addVartoStore("luminosityBlock");
    addVartoStore("event");
    addVartoStore("gen.*");
    addVartoStore("Pileup.*");
    addVartoStore("nJet");
    addVartoStore("Jet_.*");
    addVartoStore("MET.*");

    if (!_isData) {
        addVartoStore("Pileup_nPu");
        addVartoStore("Pileup_nTrueInt");
    }

    addVartoStore("nElectron");
    addVartoStore("Electron_.*");
    addVartoStore("nMuon");
    addVartoStore("Muon_.*");
    addVartoStore("nPhoton");
    addVartoStore("Photon_.*");
    addVartoStore("PV.*");
    addVartoStore("nOtherPV");
    addVartoStore("OtherPV_z");
    addVartoStore("Flag.*");

    if (!_isData) {
        addVartoStore("nGenPart");
        addVartoStore("GenPart_.*");
        addVartoStore("nLHEPart");
        addVartoStore("LHEPart_.*");
        addVartoStore("nGenJet");
        addVartoStore("GenJet_.*");
        addVartoStore("nPSWeight");
        addVartoStore("PSWeight");
        addVartoStore("nLHEPdfWeight");
        addVartoStore("LHEPdfWeight");
    }

    addVartoStore("L1PreFiringWeight*");
    addVartoStore("L1*");
    addVartoStore("HLT_Ele*");
    addVartoStore("HLT_IsoMu*");
    addVartoStore("HLT_TkMu*");
    addVartoStore("HLT_Photon*");

    // Corrected and cleaned up objects
    addVartoStore("evWeight.*");
    addVartoStore("btagWeight.*");
    addVartoStore("puWeight.*");
    addVartoStore("nelepass");
    addVartoStore("ele4vects");
    addVartoStore("nmuonpass");
    addVartoStore("muon4vects");
    addVartoStore("Sel_.*");
    addVartoStore("ncleanjets.*");
    addVartoStore("Sel2_jet.*");
    addVartoStore("cleanjet4vecs");
    addVartoStore("ncleanbjets.*");
    addVartoStore("Sel2_bjet.*");
    addVartoStore("cleanbjet4vecs.*");
    addVartoStore("nfatjetspass");
    addVartoStore("Sel_fatjet.*");
}

// Book histograms (empty for skimming if not needed)
void SkimEvents::bookHists() {
    if (debug) {
        std::cout << "================================//=================================" << std::endl;
        std::cout << "Line : " << __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout << "================================//=================================" << std::endl;
    }

    // Example histogram (may not be needed for skimming)
    add1DHist({"hcounter", "Event counter", 2, -0.5, 1.5}, "one", "evWeight", "");
}

// Set the input tree and output filename
void SkimEvents::setTree(TTree *t, std::string outfilename) {
    if (debug) {
        std::cout << "================================//=================================" << std::endl;
        std::cout << "Line : " << __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout << "================================//=================================" << std::endl;
    }

    // Setup the RDataFrame and other variables
    _rd = ROOT::RDataFrame(*t);
    _rlm = RNode(_rd);
    _outfilename = outfilename;
    _atree = t;

    // Clear any previously stored variables and histograms
    _varstostore.clear();
    _th1dhistos.clear();

    // Setup the analysis for the new tree and output file
    this->setupAnalysis();
}

// Setup any additional analysis-specific configurations
void SkimEvents::setupAnalysis() {
    if (debug) {
        std::cout << "================================//=================================" << std::endl;
        std::cout << "Line : " << __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout << "================================//=================================" << std::endl;
    }

    // Example debug output for year and run type
    std::cout << "year====" << _year << "==runtype=== " << _runtype << std::endl;

    // Define cuts, variables, histograms, and setup the tree
    defineCuts();
    defineMoreVars();
    bookHists();
    setupTree();
}
