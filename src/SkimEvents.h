/*
 * SkimEvents.h
 *
 *  Created on: Dec 9, 2018
 *      Author: suyong
 */

#ifndef SKIMEVENTS_H_
#define SKIMEVENTS_H_

#include "NanoAODAnalyzerrdframe.h"
#include <string>
#include <vector>

class SkimEvents: public NanoAODAnalyzerrdframe
{
public:
    // Constructor
    SkimEvents(TTree *t, std::string outfilename);

    // Define the cuts based on HLT triggers
    void defineCuts();

    // Define the variables to store in the output
    void defineMoreVars();

    // Book histograms (if needed, otherwise can be left empty)
    void bookHists();

    // Set the input tree and output filename
    void setTree(TTree *t, std::string outfilename);

    // Setup any additional analysis-specific configurations
    void setupAnalysis();

private:
    string _outfilename;  // Output filename

    TFile *_outrootfile;  // Output ROOT file
    vector<string> _outrootfilenames;  // List of output filenames
};

#endif /* SKIMEVENTS_H_ */
