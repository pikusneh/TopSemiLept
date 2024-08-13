#ifndef OVERLAPREMOVAL_H
#define OVERLAPREMOVAL_H

#include <vector>
#include <cmath>
#include <string>
#include "ROOT/RVec.hxx"  // Include this for ROOT::RVec


float deltaR(float eta1, float phi1, float eta2, float phi2);

std::vector<double> minGenDr(int myInd, const ROOT::RVec<float> &genPt, const ROOT::RVec<float> &genEta,
                             const ROOT::RVec<float> &genPhi, const ROOT::RVec<int> &genPdgId,
                             const ROOT::RVec<int> &genStatus, const ROOT::RVec<int> &genPartIdxMother,
                             std::vector<int> ignorePID = std::vector<int>());

bool overlapRemoval(const ROOT::RVec<float> &genPt, const ROOT::RVec<float> &genEta,
                    const ROOT::RVec<float> &genPhi, const ROOT::RVec<int> &genPdgId,
                    const ROOT::RVec<int> &genStatus, const ROOT::RVec<int> &genPartIdxMother,
                    double Et_cut, double Eta_cut, double dR_cut, bool verbose, const std::string &sample);

#endif // OVERLAPREMOVAL_H
