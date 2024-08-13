#include "overlapRemoval.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <atomic>


float deltaR(float eta1, float phi1, float eta2, float phi2)
{
    float deta = eta1 - eta2;
    float dphi = std::fabs(phi1 - phi2);
    if (dphi > M_PI)
        dphi = 2 * M_PI - dphi;
    return std::sqrt(deta * deta + dphi * dphi);
}

std::vector<double> minGenDr(int myInd, const ROOT::RVec<float> &genPt, const ROOT::RVec<float> &genEta, const ROOT::RVec<float> &genPhi, const ROOT::RVec<int> &genPdgId, const ROOT::RVec<int> &genStatus, const ROOT::RVec<int> &genPartIdxMother, std::vector<int> ignorePID)
{
    double myEta = genEta[myInd]; 
    double myPhi = genPhi[myInd];
    int myPID = genPdgId[myInd];
    
    double mindr = 999.0;
    double dr;
    int bestInd = -1;
    for (int oind = 0; oind < genPt.size(); ++oind)
    {
        if (oind == myInd) continue;
        if (genStatus[oind] != 1) continue; // check if it's final state
        if (genPt[oind] < 5)  continue;
        if (std::abs(genPt[oind] - genPt[myInd]) < 0.01 && (genPdgId[oind] == genPdgId[myInd]) && std::abs(genEta[oind] - genEta[myInd]) < 0.01)  continue; // skip if same particle
        int opid = std::abs(genPdgId[oind]);
        if (opid == 12 || opid == 14 || opid == 16) continue; // skip neutrinos
        if (std::find(ignorePID.begin(), ignorePID.end(), opid) != ignorePID.end()) continue; //skip any pid in ignorePID vector
        dr = deltaR(myEta, myPhi, genEta[oind], genPhi[oind]);
        if (mindr > dr)
        {
            //check if the second particle is a decay product of the first
            int genParentIdx = genPartIdxMother[oind];
            bool isDecay = false;
            while (genParentIdx >= myInd)
            {
                if (genParentIdx == myInd) isDecay = true;
                genParentIdx = genPartIdxMother[genParentIdx];
            }
            if (isDecay) continue;

            mindr = dr;
            bestInd = oind;
        }
    }
    std::vector<double> v;
    v.push_back(mindr);
    v.push_back((double)bestInd);
    return v;
}



bool overlapRemoval(const ROOT::RVec<float> &genPt, const ROOT::RVec<float> &genEta, const ROOT::RVec<float> &genPhi, const ROOT::RVec<int> &genPdgId, const ROOT::RVec<int> &genStatus, const ROOT::RVec<int> &genPartIdxMother, double Et_cut, double Eta_cut, double dR_cut, bool verbose, const std::string &sample)
{
    bool haveOverlap = false;
    std::vector<int> extraPIDIgnore = {22};
    for (int mcInd = 0; mcInd < genPt.size(); ++mcInd)
    {
        if (genPdgId[mcInd] == 22)
        {
            bool parentagePass = false;
            std::vector<double> minDR_Result = {-1.0, 0.0};
            bool Overlaps = false;
            int maxPDGID = 0;
            if (genPt[mcInd] >= Et_cut && std::fabs(genEta[mcInd]) <= Eta_cut)
            {
                int parentIdx = mcInd;
                int motherPDGID = 0;
                bool fromTopDecay = false;
                while (parentIdx != -1)
                {
                    motherPDGID = std::abs(genPdgId[parentIdx]);
                    maxPDGID = std::max(maxPDGID, motherPDGID);
                    parentIdx = genPartIdxMother[parentIdx];
                }

                parentagePass = maxPDGID < 37;
                if (parentagePass)
                {
                    minDR_Result = minGenDr(mcInd, genPt, genEta, genPhi, genPdgId, genStatus, genPartIdxMother, extraPIDIgnore);
                    if (minDR_Result[0] > dR_cut)
                    {
                        haveOverlap = true;
                        Overlaps = true;
                    }
                }
            }
            if (verbose)
            {
                std::cout << "Sample: " << sample << ", gen particle idx=" << mcInd << " pdgID=" << genPdgId[mcInd] << " status=" << genStatus[mcInd] << " pt=" << genPt[mcInd] << " eta=" << genEta[mcInd] << " parentage=" << (maxPDGID < 37) << " maxPDGID=" << maxPDGID << " minDR=" << minDR_Result[0] << " closestInd=" << minDR_Result[1] << " closestPDGID=" << genPdgId[(int)minDR_Result[1]] << " OVERLAPS=" << Overlaps << std::endl;
            }
        }
    }
    return haveOverlap;
}


