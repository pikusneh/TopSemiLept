#ifndef CROSSSECTIONS_H
#define CROSSSECTIONS_H

#include <map>
#include <vector>
#include <string>

// Declare the map to store cross-sections
std::map<std::string, std::vector<double>> crossSections;

// Function to initialize the cross-sections
void initCrossSections() {

    crossSections["TTbar_Dilept"] = {87.315, 87.315, 87.315};
    crossSections["TTbar_Semilept"] = {364.352, 364.352, 364.352};
    crossSections["TTbar_Hadronic"] = {380.095, 380.095, 380.095};

    crossSections["TTGamma_Dilept"] = {1.495 * 1.616, 1.495 * 1.616, 1.495 * 1.616}; // TTGamma Dilepton
    crossSections["TTGamma_Semilept"] = {5.056 * 1.994, 5.056 * 1.994, 5.056 * 1.994}; // TTGamma Single Lepton
    crossSections["TTGamma_Hadronic"] = {4.149 * 2.565, 4.149 * 2.565, 4.149 * 2.565}; // TTGamma Hadronic

    
}

#endif // CROSSSECTIONS_H
