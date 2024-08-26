/*
 * TopSemiLeptAnalyzer.h
 *
 *  Created on: May 6, 2022
 *      Author: suyong
 *		Developper: cdozen
 */

#ifndef TOPSEMILEPTANALYZER_H
#define TOPSEMILEPTANALYZER_H

#include "NanoAODAnalyzerrdframe.h"

class TopSemiLeptAnalyzer : public NanoAODAnalyzerrdframe
{
public:
	// TopSemiLeptAnalyzer(TTree *t, std::string outfilename);
	TopSemiLeptAnalyzer(TTree *tree, std::string outFileName, std::string sampleName);
	void setSampleName(const std::string &sampleName);
	void defineCuts();	   // define a series of cuts from defined variables only. you must implement this in your subclassed analysis
	void defineMoreVars(); // define higher-level variables from basic ones, you must implement this in your subclassed analysis code
	void bookHists();	   // book histograms, you must implement this in your subclassed analysis code

	void setTree(TTree *t, std::string outfilename);
	void setupObjects();
	void setupAnalysis();
	// object selectors
	void selectChannel();
	void selectElectrons();
	void selectMuons();
	void selectJets();
	void selectPhotons();
	void GenParticle4vec();
	void calculateEvWeight();
	void selectMET();
	void removeOverlaps();
	ROOT::RDF::RNode applyOverlapRemoval(ROOT::RDF::RNode df, const std::string &sample_name);
	ROOT::RDF::RNode categorizePhotons(ROOT::RDF::RNode df);
	double getlumiWeight(std::string sampleName, int year, double luminosity, double sumgenweight);

	bool debug = true;
	bool _jsonOK;
	string _outfilename;

	TFile *_outrootfile;
	vector<string> _outrootfilenames;

private:
	std::string sample_name;
	void categorizeSinglePhoton(int phoInd, const ROOT::RVec<int> &phoGenPartIdx, const ROOT::RVec<float> &phoEta, const ROOT::RVec<float> &phoPhi,
                                                 const ROOT::RVec<int> &genPartPdgId, const ROOT::RVec<float> &genPartPt, const ROOT::RVec<float> &genPartEta,
                                                 const ROOT::RVec<float> &genPartPhi, const ROOT::RVec<int> &genPartIdxMother,
                                                 const ROOT::VecOps::RVec<ROOT::Math::PtEtaPhiMVector> &genParticles_4vecs,
                                                 const ROOT::VecOps::RVec<ROOT::Math::PtEtaPhiMVector> &goodPhotons_4vecs,
                                                 bool &isGenuine, bool &isMisIDEle, bool &isHadronicPhoton, bool &isHadronicFake, bool &isPUPhoton);

								
};


#endif // TOPSEMILEPTANALYZER_H
