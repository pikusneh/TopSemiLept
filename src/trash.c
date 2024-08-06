
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
