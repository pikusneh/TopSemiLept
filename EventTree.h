#ifndef EventClass_h
#define EventClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class EventClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   UInt_t          luminosityBlock;
   ULong64_t       event;
   // Float_t         HTXS_Higgs_pt;
   // Float_t         HTXS_Higgs_y;
   // Int_t           HTXS_stage1_1_cat_pTjet25GeV;
   // Int_t           HTXS_stage1_1_cat_pTjet30GeV;
   // Int_t           HTXS_stage1_1_fine_cat_pTjet25GeV;
   // Int_t           HTXS_stage1_1_fine_cat_pTjet30GeV;
   // Int_t           HTXS_stage1_2_cat_pTjet25GeV;
   // Int_t           HTXS_stage1_2_cat_pTjet30GeV;
   // Int_t           HTXS_stage1_2_fine_cat_pTjet25GeV;
   // Int_t           HTXS_stage1_2_fine_cat_pTjet30GeV;
   // Int_t           HTXS_stage_0;
   // Int_t           HTXS_stage_1_pTjet25;
   // Int_t           HTXS_stage_1_pTjet30;
   // UChar_t         HTXS_njets25;
   // UChar_t         HTXS_njets30;
   Float_t         btagWeight_CSVV2;
   Float_t         btagWeight_CMVA;
   Float_t         CaloMET_phi;
   Float_t         CaloMET_pt;
   Float_t         CaloMET_sumEt;
   Float_t         ChsMET_phi;
   Float_t         ChsMET_pt;
   Float_t         ChsMET_sumEt;
   UInt_t          nCorrT1METJet;
   Float_t         CorrT1METJet_area[26];   //[nCorrT1METJet]
   Float_t         CorrT1METJet_eta[26];   //[nCorrT1METJet]
   Float_t         CorrT1METJet_muonSubtrFactor[26];   //[nCorrT1METJet]
   Float_t         CorrT1METJet_phi[26];   //[nCorrT1METJet]
   Float_t         CorrT1METJet_rawPt[26];   //[nCorrT1METJet]

   UInt_t          nElectron;
   Float_t         Electron_deltaEtaSC[11];   //[nElectron]
   Float_t         Electron_dr03EcalRecHitSumEt[11];   //[nElectron]
   Float_t         Electron_dr03HcalDepth1TowerSumEt[11];   //[nElectron]
   Float_t         Electron_dr03TkSumPt[11];   //[nElectron]
   Float_t         Electron_dr03TkSumPtHEEP[11];   //[nElectron]
   Float_t         Electron_dxy[11];   //[nElectron]
   Float_t         Electron_dxyErr[11];   //[nElectron]
   Float_t         Electron_dz[11];   //[nElectron]
   Float_t         Electron_dzErr[11];   //[nElectron]
   Float_t         Electron_eCorr[11];   //[nElectron]
   Float_t         Electron_eInvMinusPInv[11];   //[nElectron]
   Float_t         Electron_energyErr[11];   //[nElectron]
   Float_t         Electron_eta[11];   //[nElectron]
   Float_t         Electron_hoe[11];   //[nElectron]
   Float_t         Electron_ip3d[11];   //[nElectron]
   Float_t         Electron_jetPtRelv2[11];   //[nElectron]
   Float_t         Electron_jetRelIso[11];   //[nElectron]
   Float_t         Electron_mass[11];   //[nElectron]
   Float_t         Electron_miniPFRelIso_all[11];   //[nElectron]
   Float_t         Electron_miniPFRelIso_chg[11];   //[nElectron]
   Float_t         Electron_mvaFall17V1Iso[11];   //[nElectron]
   Float_t         Electron_mvaFall17V1noIso[11];   //[nElectron]
   Float_t         Electron_mvaFall17V2Iso[11];   //[nElectron]
   Float_t         Electron_mvaFall17V2noIso[11];   //[nElectron]
   Float_t         Electron_mvaSpring16GP[11];   //[nElectron]
   Float_t         Electron_mvaSpring16HZZ[11];   //[nElectron]
   Float_t         Electron_pfRelIso03_all[11];   //[nElectron]
   Float_t         Electron_pfRelIso03_chg[11];   //[nElectron]
   Float_t         Electron_phi[11];   //[nElectron]
   Float_t         Electron_pt[11];   //[nElectron]
   Float_t         Electron_r9[11];   //[nElectron]
   Float_t         Electron_scEtOverPt[11];   //[nElectron]
   Float_t         Electron_sieie[11];   //[nElectron]
   Float_t         Electron_sip3d[11];   //[nElectron]
   Float_t         Electron_mvaTTH[11];   //[nElectron]
   Int_t           Electron_charge[11];   //[nElectron]
   Int_t           Electron_cutBased[11];   //[nElectron]
   Int_t           Electron_cutBased_Fall17_V1[11];   //[nElectron]
   Int_t           Electron_cutBased_HLTPreSel[11];   //[nElectron]
   Int_t           Electron_cutBased_Spring15[11];   //[nElectron]
   Int_t           Electron_cutBased_Sum16[11];   //[nElectron]
   Int_t           Electron_jetIdx[11];   //[nElectron]
   Int_t           Electron_pdgId[11];   //[nElectron]
   Int_t           Electron_photonIdx[11];   //[nElectron]
   Int_t           Electron_tightCharge[11];   //[nElectron]
   Int_t           Electron_vidNestedWPBitmap[11];   //[nElectron]
   Int_t           Electron_vidNestedWPBitmapHEEP[11];   //[nElectron]
   Int_t           Electron_vidNestedWPBitmapSpring15[11];   //[nElectron]
   Int_t           Electron_vidNestedWPBitmapSum16[11];   //[nElectron]
   Bool_t          Electron_convVeto[11];   //[nElectron]
   Bool_t          Electron_cutBased_HEEP[11];   //[nElectron]
   Bool_t          Electron_isPFcand[11];   //[nElectron]
   UChar_t         Electron_lostHits[11];   //[nElectron]
   Bool_t          Electron_mvaFall17V1Iso_WP80[11];   //[nElectron]
   Bool_t          Electron_mvaFall17V1Iso_WP90[11];   //[nElectron]
   Bool_t          Electron_mvaFall17V1Iso_WPL[11];   //[nElectron]
   Bool_t          Electron_mvaFall17V1noIso_WP80[11];   //[nElectron]
   Bool_t          Electron_mvaFall17V1noIso_WP90[11];   //[nElectron]
   Bool_t          Electron_mvaFall17V1noIso_WPL[11];   //[nElectron]
   Bool_t          Electron_mvaFall17V2Iso_WP80[11];   //[nElectron]
   Bool_t          Electron_mvaFall17V2Iso_WP90[11];   //[nElectron]
   Bool_t          Electron_mvaFall17V2Iso_WPL[11];   //[nElectron]
   Bool_t          Electron_mvaFall17V2noIso_WP80[11];   //[nElectron]
   Bool_t          Electron_mvaFall17V2noIso_WP90[11];   //[nElectron]
   Bool_t          Electron_mvaFall17V2noIso_WPL[11];   //[nElectron]
   Bool_t          Electron_mvaSpring16GP_WP80[11];   //[nElectron]
   Bool_t          Electron_mvaSpring16GP_WP90[11];   //[nElectron]
   Bool_t          Electron_mvaSpring16HZZ_WPL[11];   //[nElectron]
   UChar_t         Electron_seedGain[11];   //[nElectron]

   // UInt_t          nFatJet;
   // Float_t         FatJet_area[6];   //[nFatJet]
   // Float_t         FatJet_btagCMVA[6];   //[nFatJet]
   // Float_t         FatJet_btagCSVV2[6];   //[nFatJet]
   // Float_t         FatJet_btagDDBvL[6];   //[nFatJet]
   // Float_t         FatJet_btagDDBvL_noMD[6];   //[nFatJet]
   // Float_t         FatJet_btagDDCvB[6];   //[nFatJet]
   // Float_t         FatJet_btagDDCvB_noMD[6];   //[nFatJet]
   // Float_t         FatJet_btagDDCvL[6];   //[nFatJet]
   // Float_t         FatJet_btagDDCvL_noMD[6];   //[nFatJet]
   // Float_t         FatJet_btagDeepB[6];   //[nFatJet]
   // Float_t         FatJet_btagHbb[6];   //[nFatJet]
   // Float_t         FatJet_deepTagMD_H4qvsQCD[6];   //[nFatJet]
   // Float_t         FatJet_deepTagMD_HbbvsQCD[6];   //[nFatJet]
   // Float_t         FatJet_deepTagMD_TvsQCD[6];   //[nFatJet]
   // Float_t         FatJet_deepTagMD_WvsQCD[6];   //[nFatJet]
   // Float_t         FatJet_deepTagMD_ZHbbvsQCD[6];   //[nFatJet]
   // Float_t         FatJet_deepTagMD_ZHccvsQCD[6];   //[nFatJet]
   // Float_t         FatJet_deepTagMD_ZbbvsQCD[6];   //[nFatJet]
   // Float_t         FatJet_deepTagMD_ZvsQCD[6];   //[nFatJet]
   // Float_t         FatJet_deepTagMD_bbvsLight[6];   //[nFatJet]
   // Float_t         FatJet_deepTagMD_ccvsLight[6];   //[nFatJet]
   // Float_t         FatJet_deepTag_H[6];   //[nFatJet]
   // Float_t         FatJet_deepTag_QCD[6];   //[nFatJet]
   // Float_t         FatJet_deepTag_QCDothers[6];   //[nFatJet]
   // Float_t         FatJet_deepTag_TvsQCD[6];   //[nFatJet]
   // Float_t         FatJet_deepTag_WvsQCD[6];   //[nFatJet]
   // Float_t         FatJet_deepTag_ZvsQCD[6];   //[nFatJet]
   // Float_t         FatJet_eta[6];   //[nFatJet]
   // Float_t         FatJet_mass[6];   //[nFatJet]
   // Float_t         FatJet_msoftdrop[6];   //[nFatJet]
   // Float_t         FatJet_n2b1[6];   //[nFatJet]
   // Float_t         FatJet_n3b1[6];   //[nFatJet]
   // Float_t         FatJet_phi[6];   //[nFatJet]
   // Float_t         FatJet_pt[6];   //[nFatJet]
   // Float_t         FatJet_rawFactor[6];   //[nFatJet]
   // Float_t         FatJet_tau1[6];   //[nFatJet]
   // Float_t         FatJet_tau2[6];   //[nFatJet]
   // Float_t         FatJet_tau3[6];   //[nFatJet]
   // Float_t         FatJet_tau4[6];   //[nFatJet]
   // Float_t         FatJet_lsf3[6];   //[nFatJet]
   // Int_t           FatJet_jetId[6];   //[nFatJet]
   // Int_t           FatJet_subJetIdx1[6];   //[nFatJet]
   // Int_t           FatJet_subJetIdx2[6];   //[nFatJet]
   // Int_t           FatJet_electronIdx3SJ[6];   //[nFatJet]
   // Int_t           FatJet_muonIdx3SJ[6];   //[nFatJet]

   UInt_t          nFsrPhoton;
   Float_t         FsrPhoton_dROverEt2[4];   //[nFsrPhoton]
   Float_t         FsrPhoton_eta[4];   //[nFsrPhoton]
   Float_t         FsrPhoton_phi[4];   //[nFsrPhoton]
   Float_t         FsrPhoton_pt[4];   //[nFsrPhoton]
   Float_t         FsrPhoton_relIso03[4];   //[nFsrPhoton]
   Int_t           FsrPhoton_muonIdx[4];   //[nFsrPhoton]

   UInt_t          nGenJetAK8;
   Float_t         GenJetAK8_eta[8];   //[nGenJetAK8]
   Float_t         GenJetAK8_mass[8];   //[nGenJetAK8]
   Float_t         GenJetAK8_phi[8];   //[nGenJetAK8]
   Float_t         GenJetAK8_pt[8];   //[nGenJetAK8]

   UInt_t          nGenJet;
   Float_t         GenJet_eta[25];   //[nGenJet]
   Float_t         GenJet_mass[25];   //[nGenJet]
   Float_t         GenJet_phi[25];   //[nGenJet]
   Float_t         GenJet_pt[25];   //[nGenJet]

   UInt_t          nGenPart;
   Float_t         GenPart_eta[130];   //[nGenPart]
   Float_t         GenPart_mass[130];   //[nGenPart]
   Float_t         GenPart_phi[130];   //[nGenPart]
   Float_t         GenPart_pt[130];   //[nGenPart]
   Int_t           GenPart_genPartIdxMother[130];   //[nGenPart]
   Int_t           GenPart_pdgId[130];   //[nGenPart]
   Int_t           GenPart_status[130];   //[nGenPart]
   Int_t           GenPart_statusFlags[130];   //[nGenPart]

   UInt_t          nSubGenJetAK8;
   Float_t         SubGenJetAK8_eta[16];   //[nSubGenJetAK8]
   Float_t         SubGenJetAK8_mass[16];   //[nSubGenJetAK8]
   Float_t         SubGenJetAK8_phi[16];   //[nSubGenJetAK8]
   Float_t         SubGenJetAK8_pt[16];   //[nSubGenJetAK8]

   // Float_t         Generator_binvar;
   // Float_t         Generator_scalePDF;
   // Float_t         Generator_weight;
   // Float_t         Generator_x1;
   // Float_t         Generator_x2;
   // Float_t         Generator_xpdf1;
   // Float_t         Generator_xpdf2;
   // Int_t           Generator_id1;
   // Int_t           Generator_id2;
   // UInt_t          nGenVisTau;
   // Float_t         GenVisTau_eta[4];   //[nGenVisTau]
   // Float_t         GenVisTau_mass[4];   //[nGenVisTau]
   // Float_t         GenVisTau_phi[4];   //[nGenVisTau]
   // Float_t         GenVisTau_pt[4];   //[nGenVisTau]
   // Int_t           GenVisTau_charge[4];   //[nGenVisTau]
   // Int_t           GenVisTau_genPartIdxMother[4];   //[nGenVisTau]
   // Int_t           GenVisTau_status[4];   //[nGenVisTau]

   Float_t         genWeight;
   // Float_t         LHEWeight_originalXWGTUP;
   // UInt_t          nLHEPdfWeight;
   // Float_t         LHEPdfWeight[33];   //[nLHEPdfWeight]
   // UInt_t          nLHEReweightingWeight;
   // Float_t         LHEReweightingWeight[1];   //[nLHEReweightingWeight]
   // UInt_t          nLHEScaleWeight;
   // Float_t         LHEScaleWeight[44];   //[nLHEScaleWeight]
   UInt_t          nPSWeight;
   Float_t         PSWeight[4];   //[nPSWeight]

   // UInt_t          nIsoTrack;
   // Float_t         IsoTrack_dxy[6];   //[nIsoTrack]
   // Float_t         IsoTrack_dz[6];   //[nIsoTrack]
   // Float_t         IsoTrack_eta[6];   //[nIsoTrack]
   // Float_t         IsoTrack_pfRelIso03_all[6];   //[nIsoTrack]
   // Float_t         IsoTrack_pfRelIso03_chg[6];   //[nIsoTrack]
   // Float_t         IsoTrack_phi[6];   //[nIsoTrack]
   // Float_t         IsoTrack_pt[6];   //[nIsoTrack]
   // Float_t         IsoTrack_miniPFRelIso_all[6];   //[nIsoTrack]
   // Float_t         IsoTrack_miniPFRelIso_chg[6];   //[nIsoTrack]
   // Int_t           IsoTrack_fromPV[6];   //[nIsoTrack]
   // Int_t           IsoTrack_pdgId[6];   //[nIsoTrack]
   // Bool_t          IsoTrack_isHighPurityTrack[6];   //[nIsoTrack]
   // Bool_t          IsoTrack_isPFcand[6];   //[nIsoTrack]
   // Bool_t          IsoTrack_isFromLostTrack[6];   //[nIsoTrack]

   UInt_t          nJet;
   Float_t         Jet_area[28];   //[nJet]
   Float_t         Jet_btagCMVA[28];   //[nJet]
   Float_t         Jet_btagCSVV2[28];   //[nJet]
   Float_t         Jet_btagDeepB[28];   //[nJet]
   Float_t         Jet_btagDeepC[28];   //[nJet]
   Float_t         Jet_btagDeepFlavB[28];   //[nJet]
   Float_t         Jet_btagDeepFlavC[28];   //[nJet]
   Float_t         Jet_chEmEF[28];   //[nJet]
   Float_t         Jet_chFPV0EF[28];   //[nJet]
   Float_t         Jet_chFPV1EF[28];   //[nJet]
   Float_t         Jet_chFPV2EF[28];   //[nJet]
   Float_t         Jet_chFPV3EF[28];   //[nJet]
   Float_t         Jet_chHEF[28];   //[nJet]
   Float_t         Jet_eta[28];   //[nJet]
   Float_t         Jet_mass[28];   //[nJet]
   Float_t         Jet_muEF[28];   //[nJet]
   Float_t         Jet_muonSubtrFactor[28];   //[nJet]
   Float_t         Jet_neEmEF[28];   //[nJet]
   Float_t         Jet_neHEF[28];   //[nJet]
   Float_t         Jet_phi[28];   //[nJet]
   Float_t         Jet_pt[28];   //[nJet]
   Float_t         Jet_puIdDisc[28];   //[nJet]
   Float_t         Jet_qgl[28];   //[nJet]
   Float_t         Jet_rawFactor[28];   //[nJet]
   Float_t         Jet_bRegCorr[28];   //[nJet]
   Float_t         Jet_bRegRes[28];   //[nJet]
   Float_t         Jet_cRegCorr[28];   //[nJet]
   Float_t         Jet_cRegRes[28];   //[nJet]
   Int_t           Jet_electronIdx1[28];   //[nJet]
   Int_t           Jet_electronIdx2[28];   //[nJet]
   Int_t           Jet_jetId[28];   //[nJet]
   Int_t           Jet_muonIdx1[28];   //[nJet]
   Int_t           Jet_muonIdx2[28];   //[nJet]
   Int_t           Jet_nConstituents[28];   //[nJet]
   Int_t           Jet_nElectrons[28];   //[nJet]
   Int_t           Jet_nMuons[28];   //[nJet]
   Int_t           Jet_puId[28];   //[nJet]

   Float_t         L1PreFiringWeight_Dn;
   Float_t         L1PreFiringWeight_Nom;
   Float_t         L1PreFiringWeight_Up;

   // Float_t         LHE_HT;
   // Float_t         LHE_HTIncoming;
   // Float_t         LHE_Vpt;
   // Float_t         LHE_AlphaS;
   // UChar_t         LHE_Njets;
   // UChar_t         LHE_Nb;
   // UChar_t         LHE_Nc;
   // UChar_t         LHE_Nuds;
   // UChar_t         LHE_Nglu;
   // UChar_t         LHE_NpNLO;
   // UChar_t         LHE_NpLO;

   UInt_t          nLHEPart;
   Float_t         LHEPart_pt[9];   //[nLHEPart]
   Float_t         LHEPart_eta[9];   //[nLHEPart]
   Float_t         LHEPart_phi[9];   //[nLHEPart]
   Float_t         LHEPart_mass[9];   //[nLHEPart]
   Float_t         LHEPart_incomingpz[9];   //[nLHEPart]
   Int_t           LHEPart_pdgId[9];   //[nLHEPart]
   Int_t           LHEPart_status[9];   //[nLHEPart]
   Int_t           LHEPart_spin[9];   //[nLHEPart]

   // Float_t         GenMET_phi;
   // Float_t         GenMET_pt;
   // Float_t         MET_MetUnclustEnUpDeltaX;
   // Float_t         MET_MetUnclustEnUpDeltaY;
   // Float_t         MET_covXX;
   // Float_t         MET_covXY;
   // Float_t         MET_covYY;
   // Float_t         MET_phi;
   // Float_t         MET_pt;
   // Float_t         MET_significance;
   // Float_t         MET_sumEt;
   // Float_t         MET_sumPtUnclustered;

   UInt_t          nMuon;
   Float_t         Muon_dxy[12];   //[nMuon]
   Float_t         Muon_dxyErr[12];   //[nMuon]
   Float_t         Muon_dxybs[12];   //[nMuon]
   Float_t         Muon_dz[12];   //[nMuon]
   Float_t         Muon_dzErr[12];   //[nMuon]
   Float_t         Muon_eta[12];   //[nMuon]
   Float_t         Muon_ip3d[12];   //[nMuon]
   Float_t         Muon_jetPtRelv2[12];   //[nMuon]
   Float_t         Muon_jetRelIso[12];   //[nMuon]
   Float_t         Muon_mass[12];   //[nMuon]
   Float_t         Muon_miniPFRelIso_all[12];   //[nMuon]
   Float_t         Muon_miniPFRelIso_chg[12];   //[nMuon]
   Float_t         Muon_pfRelIso03_all[12];   //[nMuon]
   Float_t         Muon_pfRelIso03_chg[12];   //[nMuon]
   Float_t         Muon_pfRelIso04_all[12];   //[nMuon]
   Float_t         Muon_phi[12];   //[nMuon]
   Float_t         Muon_pt[12];   //[nMuon]
   Float_t         Muon_ptErr[12];   //[nMuon]
   Float_t         Muon_segmentComp[12];   //[nMuon]
   Float_t         Muon_sip3d[12];   //[nMuon]
   Float_t         Muon_tkRelIso[12];   //[nMuon]
   Float_t         Muon_tunepRelPt[12];   //[nMuon]
   Float_t         Muon_mvaLowPt[12];   //[nMuon]
   Float_t         Muon_mvaTTH[12];   //[nMuon]
   Int_t           Muon_charge[12];   //[nMuon]
   Int_t           Muon_jetIdx[12];   //[nMuon]
   Int_t           Muon_nStations[12];   //[nMuon]
   Int_t           Muon_nTrackerLayers[12];   //[nMuon]
   Int_t           Muon_pdgId[12];   //[nMuon]
   Int_t           Muon_tightCharge[12];   //[nMuon]
   Int_t           Muon_fsrPhotonIdx[12];   //[nMuon]
   UChar_t         Muon_highPtId[12];   //[nMuon]
   Bool_t          Muon_highPurity[12];   //[nMuon]
   Bool_t          Muon_inTimeMuon[12];   //[nMuon]
   Bool_t          Muon_isGlobal[12];   //[nMuon]
   Bool_t          Muon_isPFcand[12];   //[nMuon]
   Bool_t          Muon_isTracker[12];   //[nMuon]
   Bool_t          Muon_looseId[12];   //[nMuon]
   Bool_t          Muon_mediumId[12];   //[nMuon]
   Bool_t          Muon_mediumPromptId[12];   //[nMuon]
   UChar_t         Muon_miniIsoId[12];   //[nMuon]
   UChar_t         Muon_multiIsoId[12];   //[nMuon]
   UChar_t         Muon_mvaId[12];   //[nMuon]
   UChar_t         Muon_pfIsoId[12];   //[nMuon]
   Bool_t          Muon_softId[12];   //[nMuon]
   Bool_t          Muon_softMvaId[12];   //[nMuon]
   Bool_t          Muon_tightId[12];   //[nMuon]
   UChar_t         Muon_tkIsoId[12];   //[nMuon]
   Bool_t          Muon_triggerIdLoose[12];   //[nMuon]

   UInt_t          nPhoton;
   Float_t         Photon_eCorr[11];   //[nPhoton]
   Float_t         Photon_energyErr[11];   //[nPhoton]
   Float_t         Photon_eta[11];   //[nPhoton]
   Float_t         Photon_hoe[11];   //[nPhoton]
   Float_t         Photon_mass[11];   //[nPhoton]
   Float_t         Photon_mvaID[11];   //[nPhoton]
   Float_t         Photon_mvaID_Fall17V1p1[11];   //[nPhoton]
   Float_t         Photon_mvaID_Spring16nonTrigV1[11];   //[nPhoton]
   Float_t         Photon_pfRelIso03_all[11];   //[nPhoton]
   Float_t         Photon_pfRelIso03_chg[11];   //[nPhoton]
   Float_t         Photon_phi[11];   //[nPhoton]
   Float_t         Photon_pt[11];   //[nPhoton]
   Float_t         Photon_r9[11];   //[nPhoton]
   Float_t         Photon_sieie[11];   //[nPhoton]
   Int_t           Photon_charge[11];   //[nPhoton]
   Int_t           Photon_cutBased[11];   //[nPhoton]
   Int_t           Photon_cutBased_Fall17V1Bitmap[11];   //[nPhoton]
   Int_t           Photon_cutBased_Spring16V2p2[11];   //[nPhoton]
   Int_t           Photon_electronIdx[11];   //[nPhoton]
   Int_t           Photon_jetIdx[11];   //[nPhoton]
   Int_t           Photon_pdgId[11];   //[nPhoton]
   Int_t           Photon_vidNestedWPBitmap[11];   //[nPhoton]
   Int_t           Photon_vidNestedWPBitmap_Spring16V2p2[11];   //[nPhoton]
   Bool_t          Photon_electronVeto[11];   //[nPhoton]
   Bool_t          Photon_isScEtaEB[11];   //[nPhoton]
   Bool_t          Photon_isScEtaEE[11];   //[nPhoton]
   Bool_t          Photon_mvaID_WP80[11];   //[nPhoton]
   Bool_t          Photon_mvaID_WP90[11];   //[nPhoton]
   Bool_t          Photon_pixelSeed[11];   //[nPhoton]
   UChar_t         Photon_seedGain[11];   //[nPhoton]

   Float_t         Pileup_nTrueInt;
   Float_t         Pileup_pudensity;
   Float_t         Pileup_gpudensity;
   Int_t           Pileup_nPU;
   Int_t           Pileup_sumEOOT;
   Int_t           Pileup_sumLOOT;

   Float_t         PuppiMET_phi;
   Float_t         PuppiMET_phiJERUp;
   Float_t         PuppiMET_phiJESUp;
   Float_t         PuppiMET_pt;
   Float_t         PuppiMET_ptJERUp;
   Float_t         PuppiMET_ptJESUp;
   Float_t         PuppiMET_sumEt;
   Float_t         RawMET_phi;
   Float_t         RawMET_pt;
   Float_t         RawMET_sumEt;
   Float_t         RawPuppiMET_phi;
   Float_t         RawPuppiMET_pt;
   Float_t         RawPuppiMET_sumEt;
   Float_t         fixedGridRhoFastjetAll;
   Float_t         fixedGridRhoFastjetCentral;
   Float_t         fixedGridRhoFastjetCentralCalo;
   Float_t         fixedGridRhoFastjetCentralChargedPileUp;
   Float_t         fixedGridRhoFastjetCentralNeutral;

   UInt_t          nGenDressedLepton;
   Float_t         GenDressedLepton_eta[3];   //[nGenDressedLepton]
   Float_t         GenDressedLepton_mass[3];   //[nGenDressedLepton]
   Float_t         GenDressedLepton_phi[3];   //[nGenDressedLepton]
   Float_t         GenDressedLepton_pt[3];   //[nGenDressedLepton]
   Int_t           GenDressedLepton_pdgId[3];   //[nGenDressedLepton]
   Bool_t          GenDressedLepton_hasTauAnc[3];   //[nGenDressedLepton]
   
   UInt_t          nGenIsolatedPhoton;
   Float_t         GenIsolatedPhoton_eta[3];   //[nGenIsolatedPhoton]
   Float_t         GenIsolatedPhoton_mass[3];   //[nGenIsolatedPhoton]
   Float_t         GenIsolatedPhoton_phi[3];   //[nGenIsolatedPhoton]
   Float_t         GenIsolatedPhoton_pt[3];   //[nGenIsolatedPhoton]

   UInt_t          nSoftActivityJet;
   Float_t         SoftActivityJet_eta[6];   //[nSoftActivityJet]
   Float_t         SoftActivityJet_phi[6];   //[nSoftActivityJet]
   Float_t         SoftActivityJet_pt[6];   //[nSoftActivityJet]

   // Float_t         SoftActivityJetHT;
   // Float_t         SoftActivityJetHT10;
   // Float_t         SoftActivityJetHT2;
   // Float_t         SoftActivityJetHT5;
   // Int_t           SoftActivityJetNjets10;
   // Int_t           SoftActivityJetNjets2;
   // Int_t           SoftActivityJetNjets5;

   UInt_t          nSubJet;
   Float_t         SubJet_btagCMVA[12];   //[nSubJet]
   Float_t         SubJet_btagCSVV2[12];   //[nSubJet]
   Float_t         SubJet_btagDeepB[12];   //[nSubJet]
   Float_t         SubJet_eta[12];   //[nSubJet]
   Float_t         SubJet_mass[12];   //[nSubJet]
   Float_t         SubJet_n2b1[12];   //[nSubJet]
   Float_t         SubJet_n3b1[12];   //[nSubJet]
   Float_t         SubJet_phi[12];   //[nSubJet]
   Float_t         SubJet_pt[12];   //[nSubJet]
   Float_t         SubJet_rawFactor[12];   //[nSubJet]
   Float_t         SubJet_tau1[12];   //[nSubJet]
   Float_t         SubJet_tau2[12];   //[nSubJet]
   Float_t         SubJet_tau3[12];   //[nSubJet]
   Float_t         SubJet_tau4[12];   //[nSubJet]

   UInt_t          nTau;
   Float_t         Tau_chargedIso[8];   //[nTau]
   Float_t         Tau_dxy[8];   //[nTau]
   Float_t         Tau_dz[8];   //[nTau]
   Float_t         Tau_eta[8];   //[nTau]
   Float_t         Tau_leadTkDeltaEta[8];   //[nTau]
   Float_t         Tau_leadTkDeltaPhi[8];   //[nTau]
   Float_t         Tau_leadTkPtOverTauPt[8];   //[nTau]
   Float_t         Tau_mass[8];   //[nTau]
   Float_t         Tau_neutralIso[8];   //[nTau]
   Float_t         Tau_phi[8];   //[nTau]
   Float_t         Tau_photonsOutsideSignalCone[8];   //[nTau]
   Float_t         Tau_pt[8];   //[nTau]
   Float_t         Tau_puCorr[8];   //[nTau]
   Float_t         Tau_rawAntiEle[8];   //[nTau]
   Float_t         Tau_rawAntiEle2018[8];   //[nTau]
   Float_t         Tau_rawDeepTau2017v2p1VSe[8];   //[nTau]
   Float_t         Tau_rawDeepTau2017v2p1VSjet[8];   //[nTau]
   Float_t         Tau_rawDeepTau2017v2p1VSmu[8];   //[nTau]
   Float_t         Tau_rawIso[8];   //[nTau]
   Float_t         Tau_rawIsodR03[8];   //[nTau]
   Float_t         Tau_rawMVAnewDM2017v2[8];   //[nTau]
   Float_t         Tau_rawMVAoldDM[8];   //[nTau]
   Float_t         Tau_rawMVAoldDM2017v1[8];   //[nTau]
   Float_t         Tau_rawMVAoldDM2017v2[8];   //[nTau]
   Float_t         Tau_rawMVAoldDMdR032017v2[8];   //[nTau]
   Int_t           Tau_charge[8];   //[nTau]
   Int_t           Tau_decayMode[8];   //[nTau]
   Int_t           Tau_jetIdx[8];   //[nTau]
   Int_t           Tau_rawAntiEleCat[8];   //[nTau]
   Int_t           Tau_rawAntiEleCat2018[8];   //[nTau]
   UChar_t         Tau_idAntiEle[8];   //[nTau]
   UChar_t         Tau_idAntiEle2018[8];   //[nTau]
   UChar_t         Tau_idAntiMu[8];   //[nTau]
   Bool_t          Tau_idDecayMode[8];   //[nTau]
   Bool_t          Tau_idDecayModeNewDMs[8];   //[nTau]
   UChar_t         Tau_idDeepTau2017v2p1VSe[8];   //[nTau]
   UChar_t         Tau_idDeepTau2017v2p1VSjet[8];   //[nTau]
   UChar_t         Tau_idDeepTau2017v2p1VSmu[8];   //[nTau]
   UChar_t         Tau_idMVAnewDM2017v2[8];   //[nTau]
   UChar_t         Tau_idMVAoldDM[8];   //[nTau]
   UChar_t         Tau_idMVAoldDM2017v1[8];   //[nTau]
   UChar_t         Tau_idMVAoldDM2017v2[8];   //[nTau]
   UChar_t         Tau_idMVAoldDMdR032017v2[8];   //[nTau]

   Float_t         TkMET_phi;
   Float_t         TkMET_pt;
   Float_t         TkMET_sumEt;

   UInt_t          nTrigObj;
   Float_t         TrigObj_pt[70];   //[nTrigObj]
   Float_t         TrigObj_eta[70];   //[nTrigObj]
   Float_t         TrigObj_phi[70];   //[nTrigObj]
   Float_t         TrigObj_l1pt[70];   //[nTrigObj]
   Float_t         TrigObj_l1pt_2[70];   //[nTrigObj]
   Float_t         TrigObj_l2pt[70];   //[nTrigObj]
   Int_t           TrigObj_id[70];   //[nTrigObj]
   Int_t           TrigObj_l1iso[70];   //[nTrigObj]
   Int_t           TrigObj_l1charge[70];   //[nTrigObj]
   Int_t           TrigObj_filterBits[70];   //[nTrigObj]

   Int_t           genTtbarId;
   UInt_t          nOtherPV;
   Float_t         OtherPV_z[3];   //[nOtherPV]
   Float_t         PV_ndof;
   Float_t         PV_x;
   Float_t         PV_y;
   Float_t         PV_z;
   Float_t         PV_chi2;
   Float_t         PV_score;
   Int_t           PV_npvs;
   Int_t           PV_npvsGood;
   UInt_t          nSV;
   Float_t         SV_dlen[14];   //[nSV]
   Float_t         SV_dlenSig[14];   //[nSV]
   Float_t         SV_dxy[14];   //[nSV]
   Float_t         SV_dxySig[14];   //[nSV]
   Float_t         SV_pAngle[14];   //[nSV]

   Int_t           Electron_genPartIdx[11];   //[nElectron]
   UChar_t         Electron_genPartFlav[11];   //[nElectron]

   Int_t           FatJet_genJetAK8Idx[6];   //[nFatJet]
   Int_t           FatJet_hadronFlavour[6];   //[nFatJet]
   UChar_t         FatJet_nBHadrons[6];   //[nFatJet]
   UChar_t         FatJet_nCHadrons[6];   //[nFatJet]

   Int_t           GenJetAK8_partonFlavour[8];   //[nGenJetAK8]
   UChar_t         GenJetAK8_hadronFlavour[8];   //[nGenJetAK8]

   Int_t           GenJet_partonFlavour[25];   //[nGenJet]
   UChar_t         GenJet_hadronFlavour[25];   //[nGenJet]

   Int_t           Jet_genJetIdx[28];   //[nJet]
   Int_t           Jet_hadronFlavour[28];   //[nJet]
   Int_t           Jet_partonFlavour[28];   //[nJet]

   Int_t           Muon_genPartIdx[12];   //[nMuon]
   UChar_t         Muon_genPartFlav[12];   //[nMuon]

   Int_t           Photon_genPartIdx[11];   //[nPhoton]
   UChar_t         Photon_genPartFlav[11];   //[nPhoton]

   Float_t         MET_fiducialGenPhi;
   Float_t         MET_fiducialGenPt;
   UChar_t         Electron_cleanmask[11];   //[nElectron]
   UChar_t         Jet_cleanmask[28];   //[nJet]
   UChar_t         Muon_cleanmask[12];   //[nMuon]
   UChar_t         Photon_cleanmask[11];   //[nPhoton]
   UChar_t         Tau_cleanmask[8];   //[nTau]
   UChar_t         SubJet_nBHadrons[12];   //[nSubJet]
   UChar_t         SubJet_nCHadrons[12];   //[nSubJet]

   Float_t         SV_chi2[14];   //[nSV] //secondary vertex
   Float_t         SV_eta[14];   //[nSV]
   Float_t         SV_mass[14];   //[nSV]
   Float_t         SV_ndof[14];   //[nSV]
   Float_t         SV_phi[14];   //[nSV]
   Float_t         SV_pt[14];   //[nSV]
   Float_t         SV_x[14];   //[nSV]
   Float_t         SV_y[14];   //[nSV]
   Float_t         SV_z[14];   //[nSV]

   Int_t           Tau_genPartIdx[8];   //[nTau]
   UChar_t         Tau_genPartFlav[8];   //[nTau]

   Bool_t          L1_AlwaysTrue;
   Bool_t          L1_BRIL_TRIG0_AND;
   Bool_t          L1_BRIL_TRIG0_FstBunchInTrain;
   Bool_t          L1_BRIL_TRIG0_OR;
   Bool_t          L1_BRIL_TRIG0_delayedAND;
   Bool_t          L1_BeamGasB1;
   Bool_t          L1_BeamGasB2;
   Bool_t          L1_BeamGasMinus;
   Bool_t          L1_BeamGasPlus;
   Bool_t          L1_BptxMinus;
   Bool_t          L1_BptxOR;
   Bool_t          L1_BptxPlus;
   Bool_t          L1_BptxXOR;
   Bool_t          L1_CASTOR_Gap_BptxAND;
   Bool_t          L1_CASTOR_HaloMuon;
   Bool_t          L1_CASTOR_HaloMuon_BptxAND;
   Bool_t          L1_CASTOR_HighJet_BptxAND;
   Bool_t          L1_CASTOR_MediumJet_BptxAND;
   Bool_t          L1_DoubleEG6_HTT255;
   Bool_t          L1_DoubleEG_15_10;
   Bool_t          L1_DoubleEG_18_17;
   Bool_t          L1_DoubleEG_20_18;
   Bool_t          L1_DoubleEG_22_10;
   Bool_t          L1_DoubleEG_22_12;
   Bool_t          L1_DoubleEG_22_15;
   Bool_t          L1_DoubleEG_23_10;
   Bool_t          L1_DoubleEG_24_17;
   Bool_t          L1_DoubleEG_25_12;
   Bool_t          L1_DoubleIsoTau28er;
   Bool_t          L1_DoubleIsoTau30er;
   Bool_t          L1_DoubleIsoTau32er;
   Bool_t          L1_DoubleIsoTau33er;
   Bool_t          L1_DoubleIsoTau34er;
   Bool_t          L1_DoubleIsoTau35er;
   Bool_t          L1_DoubleIsoTau36er;
   Bool_t          L1_DoubleJet12_ForwardBackward;
   Bool_t          L1_DoubleJet16_ForwardBackward;
   Bool_t          L1_DoubleJet30_Mj30j30_400_Mu10;
   Bool_t          L1_DoubleJet30_Mj30j30_400_Mu6;
   Bool_t          L1_DoubleJet8_ForwardBackward;
   Bool_t          L1_DoubleJetC100;
   Bool_t          L1_DoubleJetC112;
   Bool_t          L1_DoubleJetC120;
   Bool_t          L1_DoubleJetC40;
   Bool_t          L1_DoubleJetC50;
   Bool_t          L1_DoubleJetC60;
   Bool_t          L1_DoubleJetC60_ETM60;
   Bool_t          L1_DoubleJetC80;
   Bool_t          L1_DoubleJet_100_30_Mj30j30_620;
   Bool_t          L1_DoubleJet_90_30_Mj30j30_620;
   Bool_t          L1_DoubleMu0;
   Bool_t          L1_DoubleMu0_ETM40;
   Bool_t          L1_DoubleMu0_ETM55;
   Bool_t          L1_DoubleMu0_ETM60;
   Bool_t          L1_DoubleMu0_ETM65;
   Bool_t          L1_DoubleMu0_ETM70;
   Bool_t          L1_DoubleMu0er1p4_dEta_Max1p8_OS;
   Bool_t          L1_DoubleMu0er1p6_dEta_Max1p8;
   Bool_t          L1_DoubleMu0er1p6_dEta_Max1p8_OS;
   Bool_t          L1_DoubleMu7_EG14;
   Bool_t          L1_DoubleMu7_EG7;
   Bool_t          L1_DoubleMuOpen;
   Bool_t          L1_DoubleMu_10_0_dEta_Max1p8;
   Bool_t          L1_DoubleMu_10_3p5;
   Bool_t          L1_DoubleMu_10_Open;
   Bool_t          L1_DoubleMu_11_4;
   Bool_t          L1_DoubleMu_12_5;
   Bool_t          L1_DoubleMu_12_8;
   Bool_t          L1_DoubleMu_13_6;
   Bool_t          L1_DoubleMu_15_5;
   Bool_t          L1_DoubleTau50er;
   Bool_t          L1_DoubleTau70er;
   Bool_t          L1_EG25er_HTT125;
   Bool_t          L1_EG27er_HTT200;
   Bool_t          L1_ETM100;
   Bool_t          L1_ETM105;
   Bool_t          L1_ETM110;
   Bool_t          L1_ETM115;
   Bool_t          L1_ETM120;
   Bool_t          L1_ETM30;
   Bool_t          L1_ETM40;
   Bool_t          L1_ETM50;
   Bool_t          L1_ETM60;
   Bool_t          L1_ETM70;
   Bool_t          L1_ETM75;
   Bool_t          L1_ETM75_Jet60_dPhi_Min0p4;
   Bool_t          L1_ETM80;
   Bool_t          L1_ETM85;
   Bool_t          L1_ETM90;
   Bool_t          L1_ETM95;
   Bool_t          L1_ETT25;
   Bool_t          L1_ETT40_BptxAND;
   Bool_t          L1_ETT50_BptxAND;
   Bool_t          L1_ETT55_BptxAND;
   Bool_t          L1_ETT60_BptxAND;
   Bool_t          L1_ETT70_BptxAND;
   Bool_t          L1_ETT75_BptxAND;
   Bool_t          L1_FirstBunchAfterTrain;
   Bool_t          L1_FirstBunchInTrain;
   Bool_t          L1_HTM100;
   Bool_t          L1_HTM120;
   Bool_t          L1_HTM130;
   Bool_t          L1_HTM140;
   Bool_t          L1_HTM150;
   Bool_t          L1_HTM50;
   Bool_t          L1_HTM60_HTT260;
   Bool_t          L1_HTM70;
   Bool_t          L1_HTM80;
   Bool_t          L1_HTM80_HTT220;
   Bool_t          L1_HTT120;
   Bool_t          L1_HTT160;
   Bool_t          L1_HTT200;
   Bool_t          L1_HTT220;
   Bool_t          L1_HTT240;
   Bool_t          L1_HTT255;
   Bool_t          L1_HTT270;
   Bool_t          L1_HTT280;
   Bool_t          L1_HTT300;
   Bool_t          L1_HTT320;
   Bool_t          L1_IsoEG18er_IsoTau24er_dEta_Min0p2;
   Bool_t          L1_IsoEG20er_IsoTau25er_dEta_Min0p2;
   Bool_t          L1_IsoEG22er_IsoTau26er_dEta_Min0p2;
   Bool_t          L1_IsoEG22er_Tau20er_dEta_Min0p2;
   Bool_t          L1_IsolatedBunch;
   Bool_t          L1_Jet32_DoubleMu_10_0_dPhi_Jet_Mu0_Max0p4_dPhi_Mu_Mu_Min1p0;
   Bool_t          L1_Jet32_Mu0_EG10_dPhi_Jet_Mu_Max0p4_dPhi_Mu_EG_Min1p0;
   Bool_t          L1_MU20_EG15;
   Bool_t          L1_MinimumBiasHF0_AND;
   Bool_t          L1_MinimumBiasHF0_AND_BptxAND;
   Bool_t          L1_MinimumBiasHF0_OR;
   Bool_t          L1_MinimumBiasHF0_OR_BptxAND;
   Bool_t          L1_MinimumBiasHF1_AND;
   Bool_t          L1_MinimumBiasHF1_AND_BptxAND;
   Bool_t          L1_MinimumBiasHF1_OR;
   Bool_t          L1_MinimumBiasHF1_OR_BptxAND;
   Bool_t          L1_Mu0er_ETM40;
   Bool_t          L1_Mu0er_ETM55;
   Bool_t          L1_Mu10er_ETM30;
   Bool_t          L1_Mu10er_ETM50;
   Bool_t          L1_Mu12_EG10;
   Bool_t          L1_Mu14er_ETM30;
   Bool_t          L1_Mu16er_Tau20er;
   Bool_t          L1_Mu16er_Tau24er;
   Bool_t          L1_Mu18er_IsoTau26er;
   Bool_t          L1_Mu18er_Tau20er;
   Bool_t          L1_Mu18er_Tau24er;
   Bool_t          L1_Mu20_EG10;
   Bool_t          L1_Mu20_EG17;
   Bool_t          L1_Mu20_IsoEG6;
   Bool_t          L1_Mu20er_IsoTau26er;
   Bool_t          L1_Mu22er_IsoTau26er;
   Bool_t          L1_Mu23_EG10;
   Bool_t          L1_Mu23_IsoEG10;
   Bool_t          L1_Mu25er_IsoTau26er;
   Bool_t          L1_Mu3_JetC120;
   Bool_t          L1_Mu3_JetC120_dEta_Max0p4_dPhi_Max0p4;
   Bool_t          L1_Mu3_JetC16;
   Bool_t          L1_Mu3_JetC16_dEta_Max0p4_dPhi_Max0p4;
   Bool_t          L1_Mu3_JetC60;
   Bool_t          L1_Mu3_JetC60_dEta_Max0p4_dPhi_Max0p4;
   Bool_t          L1_Mu5_EG15;
   Bool_t          L1_Mu5_EG20;
   Bool_t          L1_Mu5_EG23;
   Bool_t          L1_Mu5_IsoEG18;
   Bool_t          L1_Mu5_IsoEG20;
   Bool_t          L1_Mu6_DoubleEG10;
   Bool_t          L1_Mu6_DoubleEG17;
   Bool_t          L1_Mu6_HTT200;
   Bool_t          L1_Mu8_HTT150;
   Bool_t          L1_NotBptxOR;
   Bool_t          L1_QuadJetC36_Tau52;
   Bool_t          L1_QuadJetC40;
   Bool_t          L1_QuadJetC50;
   Bool_t          L1_QuadJetC60;
   Bool_t          L1_QuadMu0;
   Bool_t          L1_SingleEG10;
   Bool_t          L1_SingleEG15;
   Bool_t          L1_SingleEG18;
   Bool_t          L1_SingleEG24;
   Bool_t          L1_SingleEG26;
   Bool_t          L1_SingleEG28;
   Bool_t          L1_SingleEG2_BptxAND;
   Bool_t          L1_SingleEG30;
   Bool_t          L1_SingleEG32;
   Bool_t          L1_SingleEG34;
   Bool_t          L1_SingleEG36;
   Bool_t          L1_SingleEG38;
   Bool_t          L1_SingleEG40;
   Bool_t          L1_SingleEG45;
   Bool_t          L1_SingleEG5;
   Bool_t          L1_SingleIsoEG18;
   Bool_t          L1_SingleIsoEG18er;
   Bool_t          L1_SingleIsoEG20;
   Bool_t          L1_SingleIsoEG20er;
   Bool_t          L1_SingleIsoEG22;
   Bool_t          L1_SingleIsoEG22er;
   Bool_t          L1_SingleIsoEG24;
   Bool_t          L1_SingleIsoEG24er;
   Bool_t          L1_SingleIsoEG26;
   Bool_t          L1_SingleIsoEG26er;
   Bool_t          L1_SingleIsoEG28;
   Bool_t          L1_SingleIsoEG28er;
   Bool_t          L1_SingleIsoEG30;
   Bool_t          L1_SingleIsoEG30er;
   Bool_t          L1_SingleIsoEG32;
   Bool_t          L1_SingleIsoEG32er;
   Bool_t          L1_SingleIsoEG34;
   Bool_t          L1_SingleIsoEG34er;
   Bool_t          L1_SingleIsoEG36;
   Bool_t          L1_SingleJet120;
   Bool_t          L1_SingleJet12_BptxAND;
   Bool_t          L1_SingleJet140;
   Bool_t          L1_SingleJet150;
   Bool_t          L1_SingleJet16;
   Bool_t          L1_SingleJet160;
   Bool_t          L1_SingleJet170;
   Bool_t          L1_SingleJet180;
   Bool_t          L1_SingleJet20;
   Bool_t          L1_SingleJet200;
   Bool_t          L1_SingleJet35;
   Bool_t          L1_SingleJet60;
   Bool_t          L1_SingleJet8_BptxAND;
   Bool_t          L1_SingleJet90;
   Bool_t          L1_SingleJetC20_NotBptxOR;
   Bool_t          L1_SingleJetC20_NotBptxOR_3BX;
   Bool_t          L1_SingleJetC40_NotBptxOR_3BX;
   Bool_t          L1_SingleJetC40_NotBptxOR_5BX;
   Bool_t          L1_SingleMu10_LowQ;
   Bool_t          L1_SingleMu12;
   Bool_t          L1_SingleMu14;
   Bool_t          L1_SingleMu14er;
   Bool_t          L1_SingleMu16;
   Bool_t          L1_SingleMu16er;
   Bool_t          L1_SingleMu18;
   Bool_t          L1_SingleMu18er;
   Bool_t          L1_SingleMu20;
   Bool_t          L1_SingleMu20er;
   Bool_t          L1_SingleMu22;
   Bool_t          L1_SingleMu22er;
   Bool_t          L1_SingleMu25;
   Bool_t          L1_SingleMu25er;
   Bool_t          L1_SingleMu3;
   Bool_t          L1_SingleMu30;
   Bool_t          L1_SingleMu30er;
   Bool_t          L1_SingleMu5;
   Bool_t          L1_SingleMu7;
   Bool_t          L1_SingleMuCosmics;
   Bool_t          L1_SingleMuOpen;
   Bool_t          L1_SingleMuOpen_NotBptxOR;
   Bool_t          L1_SingleMuOpen_NotBptxOR_3BX;
   Bool_t          L1_SingleTau100er;
   Bool_t          L1_SingleTau120er;
   Bool_t          L1_SingleTau80er;
   Bool_t          L1_TripleEG_14_10_8;
   Bool_t          L1_TripleEG_18_17_8;
   Bool_t          L1_TripleJet_84_68_48_VBF;
   Bool_t          L1_TripleJet_88_72_56_VBF;
   Bool_t          L1_TripleJet_92_76_64_VBF;
   Bool_t          L1_TripleMu0;
   Bool_t          L1_TripleMu_5_0_0;
   Bool_t          L1_TripleMu_5_5_3;
   Bool_t          L1_ZeroBias;
   Bool_t          L1_ZeroBias_FirstCollidingBunch;
   Bool_t          L1_ZeroBias_copy;
   Bool_t          Flag_HBHENoiseFilter;
   Bool_t          Flag_HBHENoiseIsoFilter;
   Bool_t          Flag_CSCTightHaloFilter;
   Bool_t          Flag_CSCTightHaloTrkMuUnvetoFilter;
   Bool_t          Flag_CSCTightHalo2015Filter;
   Bool_t          Flag_globalTightHalo2016Filter;
   Bool_t          Flag_globalSuperTightHalo2016Filter;
   Bool_t          Flag_HcalStripHaloFilter;
   Bool_t          Flag_hcalLaserEventFilter;
   Bool_t          Flag_EcalDeadCellTriggerPrimitiveFilter;
   Bool_t          Flag_EcalDeadCellBoundaryEnergyFilter;
   Bool_t          Flag_ecalBadCalibFilter;
   Bool_t          Flag_goodVertices;
   Bool_t          Flag_eeBadScFilter;
   Bool_t          Flag_ecalLaserCorrFilter;
   Bool_t          Flag_trkPOGFilters;
   Bool_t          Flag_chargedHadronTrackResolutionFilter;
   Bool_t          Flag_muonBadTrackFilter;
   Bool_t          Flag_BadChargedCandidateFilter;
   Bool_t          Flag_BadPFMuonFilter;
   Bool_t          Flag_BadChargedCandidateSummer16Filter;
   Bool_t          Flag_BadPFMuonSummer16Filter;
   Bool_t          Flag_trkPOG_manystripclus53X;
   Bool_t          Flag_trkPOG_toomanystripclus53X;
   Bool_t          Flag_trkPOG_logErrorTooManyClusters;
   Bool_t          Flag_METFilters;
   Bool_t          L1simulation_step;
   Bool_t          HLTriggerFirstPath;
   Bool_t          HLT_AK8PFJet360_TrimMass30;
   Bool_t          HLT_AK8PFJet400_TrimMass30;
   Bool_t          HLT_AK8PFHT750_TrimMass50;
   Bool_t          HLT_AK8PFHT800_TrimMass50;
   Bool_t          HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20;
   Bool_t          HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087;
   Bool_t          HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087;
   Bool_t          HLT_AK8DiPFJet300_200_TrimMass30;
   Bool_t          HLT_AK8PFHT700_TrimR0p1PT0p03Mass50;
   Bool_t          HLT_AK8PFHT650_TrimR0p1PT0p03Mass50;
   Bool_t          HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20;
   Bool_t          HLT_AK8DiPFJet280_200_TrimMass30;
   Bool_t          HLT_AK8DiPFJet250_200_TrimMass30;
   Bool_t          HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20;
   Bool_t          HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20;
   Bool_t          HLT_CaloJet260;
   Bool_t          HLT_CaloJet500_NoJetID;
   Bool_t          HLT_Dimuon13_PsiPrime;
   Bool_t          HLT_Dimuon13_Upsilon;
   Bool_t          HLT_Dimuon20_Jpsi;
   Bool_t          HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf;
   Bool_t          HLT_DoubleEle25_CaloIdL_GsfTrkIdVL;
   Bool_t          HLT_DoubleEle33_CaloIdL;
   Bool_t          HLT_DoubleEle33_CaloIdL_MW;
   Bool_t          HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW;
   Bool_t          HLT_DoubleEle33_CaloIdL_GsfTrkIdVL;
   Bool_t          HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg;
   Bool_t          HLT_DoubleTightCombinedIsoPFTau35_Trk1_eta2p1_Reg;
   Bool_t          HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1_Reg;
   Bool_t          HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1_Reg;
   Bool_t          HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1;
   Bool_t          HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1;
   Bool_t          HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg;
   Bool_t          HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg;
   Bool_t          HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1;
   Bool_t          HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL;
   Bool_t          HLT_DoubleMu33NoFiltersNoVtx;
   Bool_t          HLT_DoubleMu38NoFiltersNoVtx;
   Bool_t          HLT_DoubleMu23NoFiltersNoVtxDisplaced;
   Bool_t          HLT_DoubleMu28NoFiltersNoVtxDisplaced;
   Bool_t          HLT_DoubleMu0;
   Bool_t          HLT_DoubleMu4_3_Bs;
   Bool_t          HLT_DoubleMu4_3_Jpsi_Displaced;
   Bool_t          HLT_DoubleMu4_JpsiTrk_Displaced;
   Bool_t          HLT_DoubleMu4_LowMassNonResonantTrk_Displaced;
   Bool_t          HLT_DoubleMu3_Trk_Tau3mu;
   Bool_t          HLT_DoubleMu4_PsiPrimeTrk_Displaced;
   Bool_t          HLT_Mu7p5_L2Mu2_Jpsi;
   Bool_t          HLT_Mu7p5_L2Mu2_Upsilon;
   Bool_t          HLT_Mu7p5_Track2_Jpsi;
   Bool_t          HLT_Mu7p5_Track3p5_Jpsi;
   Bool_t          HLT_Mu7p5_Track7_Jpsi;
   Bool_t          HLT_Mu7p5_Track2_Upsilon;
   Bool_t          HLT_Mu7p5_Track3p5_Upsilon;
   Bool_t          HLT_Mu7p5_Track7_Upsilon;
   Bool_t          HLT_Dimuon0er16_Jpsi_NoOS_NoVertexing;
   Bool_t          HLT_Dimuon0er16_Jpsi_NoVertexing;
   Bool_t          HLT_Dimuon6_Jpsi_NoVertexing;
   Bool_t          HLT_Photon150;
   Bool_t          HLT_Photon90_CaloIdL_HT300;
   Bool_t          HLT_HT250_CaloMET70;
   Bool_t          HLT_DoublePhoton60;
   Bool_t          HLT_DoublePhoton85;
   Bool_t          HLT_Ele17_Ele8_Gsf;
   Bool_t          HLT_Ele20_eta2p1_WPLoose_Gsf_LooseIsoPFTau28;
   Bool_t          HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau29;
   Bool_t          HLT_Ele22_eta2p1_WPLoose_Gsf;
   Bool_t          HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1;
   Bool_t          HLT_Ele23_WPLoose_Gsf;
   Bool_t          HLT_Ele23_WPLoose_Gsf_WHbbBoost;
   Bool_t          HLT_Ele24_eta2p1_WPLoose_Gsf;
   Bool_t          HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20;
   Bool_t          HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1;
   Bool_t          HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30;
   Bool_t          HLT_Ele25_WPTight_Gsf;
   Bool_t          HLT_Ele25_eta2p1_WPLoose_Gsf;
   Bool_t          HLT_Ele25_eta2p1_WPTight_Gsf;
   Bool_t          HLT_Ele27_WPLoose_Gsf;
   Bool_t          HLT_Ele27_WPLoose_Gsf_WHbbBoost;
   Bool_t          HLT_Ele27_WPTight_Gsf;
   Bool_t          HLT_Ele27_WPTight_Gsf_L1JetTauSeeded;
   Bool_t          HLT_Ele27_eta2p1_WPLoose_Gsf;
   Bool_t          HLT_Ele27_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1;
   Bool_t          HLT_Ele27_eta2p1_WPTight_Gsf;
   Bool_t          HLT_Ele30_WPTight_Gsf;
   Bool_t          HLT_Ele30_eta2p1_WPLoose_Gsf;
   Bool_t          HLT_Ele30_eta2p1_WPTight_Gsf;
   Bool_t          HLT_Ele32_WPTight_Gsf;
   Bool_t          HLT_Ele32_eta2p1_WPLoose_Gsf;
   Bool_t          HLT_Ele32_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1;
   Bool_t          HLT_Ele32_eta2p1_WPTight_Gsf;
   Bool_t          HLT_Ele35_WPLoose_Gsf;
   Bool_t          HLT_Ele35_CaloIdVT_GsfTrkIdT_PFJet150_PFJet50;
   Bool_t          HLT_Ele36_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1;
   Bool_t          HLT_Ele45_WPLoose_Gsf;
   Bool_t          HLT_Ele45_WPLoose_Gsf_L1JetTauSeeded;
   Bool_t          HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50;
   Bool_t          HLT_Ele105_CaloIdVT_GsfTrkIdT;
   Bool_t          HLT_Ele30WP60_SC4_Mass55;
   Bool_t          HLT_Ele30WP60_Ele8_Mass55;
   Bool_t          HLT_HT200;
   Bool_t          HLT_HT275;
   Bool_t          HLT_HT325;
   Bool_t          HLT_HT425;
   Bool_t          HLT_HT575;
   Bool_t          HLT_HT410to430;
   Bool_t          HLT_HT430to450;
   Bool_t          HLT_HT450to470;
   Bool_t          HLT_HT470to500;
   Bool_t          HLT_HT500to550;
   Bool_t          HLT_HT550to650;
   Bool_t          HLT_HT650;
   Bool_t          HLT_Mu16_eta2p1_MET30;
   Bool_t          HLT_IsoMu16_eta2p1_MET30;
   Bool_t          HLT_IsoMu16_eta2p1_MET30_LooseIsoPFTau50_Trk30_eta2p1;
   Bool_t          HLT_IsoMu17_eta2p1;
   Bool_t          HLT_IsoMu17_eta2p1_LooseIsoPFTau20;
   Bool_t          HLT_IsoMu17_eta2p1_LooseIsoPFTau20_SingleL1;
   Bool_t          HLT_DoubleIsoMu17_eta2p1;
   Bool_t          HLT_DoubleIsoMu17_eta2p1_noDzCut;
   Bool_t          HLT_IsoMu18;
   Bool_t          HLT_IsoMu19_eta2p1_LooseIsoPFTau20;
   Bool_t          HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1;
   Bool_t          HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg;
   Bool_t          HLT_IsoMu19_eta2p1_LooseCombinedIsoPFTau20;
   Bool_t          HLT_IsoMu19_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg;
   Bool_t          HLT_IsoMu19_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg;
   Bool_t          HLT_IsoMu21_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg;
   Bool_t          HLT_IsoMu21_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg;
   Bool_t          HLT_IsoMu20;
   Bool_t          HLT_IsoMu21_eta2p1_LooseIsoPFTau20_SingleL1;
   Bool_t          HLT_IsoMu21_eta2p1_LooseIsoPFTau50_Trk30_eta2p1_SingleL1;
   Bool_t          HLT_IsoMu21_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg;
   Bool_t          HLT_IsoMu22;
   Bool_t          HLT_IsoMu22_eta2p1;
   Bool_t          HLT_IsoMu24;
   Bool_t          HLT_IsoMu27;
   Bool_t          HLT_IsoTkMu18;
   Bool_t          HLT_IsoTkMu20;
   Bool_t          HLT_IsoTkMu22;
   Bool_t          HLT_IsoTkMu22_eta2p1;
   Bool_t          HLT_IsoTkMu24;
   Bool_t          HLT_IsoTkMu27;
   Bool_t          HLT_JetE30_NoBPTX3BX;
   Bool_t          HLT_JetE30_NoBPTX;
   Bool_t          HLT_JetE50_NoBPTX3BX;
   Bool_t          HLT_JetE70_NoBPTX3BX;
   Bool_t          HLT_L1SingleMu18;
   Bool_t          HLT_L2Mu10;
   Bool_t          HLT_L1SingleMuOpen;
   Bool_t          HLT_L1SingleMuOpen_DT;
   Bool_t          HLT_L2DoubleMu23_NoVertex;
   Bool_t          HLT_L2DoubleMu28_NoVertex_2Cha_Angle2p5_Mass10;
   Bool_t          HLT_L2DoubleMu38_NoVertex_2Cha_Angle2p5_Mass10;
   Bool_t          HLT_L2Mu10_NoVertex_NoBPTX3BX;
   Bool_t          HLT_L2Mu10_NoVertex_NoBPTX;
   Bool_t          HLT_L2Mu45_NoVertex_3Sta_NoBPTX3BX;
   Bool_t          HLT_L2Mu40_NoVertex_3Sta_NoBPTX3BX;
   Bool_t          HLT_LooseIsoPFTau50_Trk30_eta2p1;
   Bool_t          HLT_LooseIsoPFTau50_Trk30_eta2p1_MET80;
   Bool_t          HLT_LooseIsoPFTau50_Trk30_eta2p1_MET90;
   Bool_t          HLT_LooseIsoPFTau50_Trk30_eta2p1_MET110;
   Bool_t          HLT_LooseIsoPFTau50_Trk30_eta2p1_MET120;
   Bool_t          HLT_PFTau120_eta2p1;
   Bool_t          HLT_PFTau140_eta2p1;
   Bool_t          HLT_VLooseIsoPFTau120_Trk50_eta2p1;
   Bool_t          HLT_VLooseIsoPFTau140_Trk50_eta2p1;
   Bool_t          HLT_Mu17_Mu8;
   Bool_t          HLT_Mu17_Mu8_DZ;
   Bool_t          HLT_Mu17_Mu8_SameSign;
   Bool_t          HLT_Mu17_Mu8_SameSign_DZ;
   Bool_t          HLT_Mu20_Mu10;
   Bool_t          HLT_Mu20_Mu10_DZ;
   Bool_t          HLT_Mu20_Mu10_SameSign;
   Bool_t          HLT_Mu20_Mu10_SameSign_DZ;
   Bool_t          HLT_Mu17_TkMu8_DZ;
   Bool_t          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;
   Bool_t          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
   Bool_t          HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
   Bool_t          HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
   Bool_t          HLT_Mu25_TkMu0_dEta18_Onia;
   Bool_t          HLT_Mu27_TkMu8;
   Bool_t          HLT_Mu30_TkMu11;
   Bool_t          HLT_Mu30_eta2p1_PFJet150_PFJet50;
   Bool_t          HLT_Mu40_TkMu11;
   Bool_t          HLT_Mu40_eta2p1_PFJet200_PFJet50;
   Bool_t          HLT_Mu20;
   Bool_t          HLT_TkMu17;
   Bool_t          HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
   Bool_t          HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
   Bool_t          HLT_TkMu20;
   Bool_t          HLT_Mu24_eta2p1;
   Bool_t          HLT_TkMu24_eta2p1;
   Bool_t          HLT_Mu27;
   Bool_t          HLT_TkMu27;
   Bool_t          HLT_Mu45_eta2p1;
   Bool_t          HLT_Mu50;
   Bool_t          HLT_TkMu50;
   Bool_t          HLT_Mu38NoFiltersNoVtx_Photon38_CaloIdL;
   Bool_t          HLT_Mu42NoFiltersNoVtx_Photon42_CaloIdL;
   Bool_t          HLT_Mu28NoFiltersNoVtxDisplaced_Photon28_CaloIdL;
   Bool_t          HLT_Mu33NoFiltersNoVtxDisplaced_Photon33_CaloIdL;
   Bool_t          HLT_Mu23NoFiltersNoVtx_Photon23_CaloIdL;
   Bool_t          HLT_DoubleMu18NoFiltersNoVtx;
   Bool_t          HLT_Mu33NoFiltersNoVtxDisplaced_DisplacedJet50_Tight;
   Bool_t          HLT_Mu33NoFiltersNoVtxDisplaced_DisplacedJet50_Loose;
   Bool_t          HLT_Mu28NoFiltersNoVtx_DisplacedJet40_Loose;
   Bool_t          HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Tight;
   Bool_t          HLT_Mu38NoFiltersNoVtxDisplaced_DisplacedJet60_Loose;
   Bool_t          HLT_Mu38NoFiltersNoVtx_DisplacedJet60_Loose;
   Bool_t          HLT_Mu28NoFiltersNoVtx_CentralCaloJet40;
   Bool_t          HLT_PFHT300_PFMET100;
   Bool_t          HLT_PFHT300_PFMET110;
   Bool_t          HLT_PFHT550_4JetPt50;
   Bool_t          HLT_PFHT650_4JetPt50;
   Bool_t          HLT_PFHT750_4JetPt50;
   Bool_t          HLT_PFHT750_4JetPt70;
   Bool_t          HLT_PFHT750_4JetPt80;
   Bool_t          HLT_PFHT800_4JetPt50;
   Bool_t          HLT_PFHT850_4JetPt50;
   Bool_t          HLT_PFJet15_NoCaloMatched;
   Bool_t          HLT_PFJet25_NoCaloMatched;
   Bool_t          HLT_DiPFJet15_NoCaloMatched;
   Bool_t          HLT_DiPFJet25_NoCaloMatched;
   Bool_t          HLT_DiPFJet15_FBEta3_NoCaloMatched;
   Bool_t          HLT_DiPFJet25_FBEta3_NoCaloMatched;
   Bool_t          HLT_DiPFJetAve15_HFJEC;
   Bool_t          HLT_DiPFJetAve25_HFJEC;
   Bool_t          HLT_DiPFJetAve35_HFJEC;
   Bool_t          HLT_AK8PFJet40;
   Bool_t          HLT_AK8PFJet60;
   Bool_t          HLT_AK8PFJet80;
   Bool_t          HLT_AK8PFJet140;
   Bool_t          HLT_AK8PFJet200;
   Bool_t          HLT_AK8PFJet260;
   Bool_t          HLT_AK8PFJet320;
   Bool_t          HLT_AK8PFJet400;
   Bool_t          HLT_AK8PFJet450;
   Bool_t          HLT_AK8PFJet500;
   Bool_t          HLT_PFJet40;
   Bool_t          HLT_PFJet60;
   Bool_t          HLT_PFJet80;
   Bool_t          HLT_PFJet140;
   Bool_t          HLT_PFJet200;
   Bool_t          HLT_PFJet260;
   Bool_t          HLT_PFJet320;
   Bool_t          HLT_PFJet400;
   Bool_t          HLT_PFJet450;
   Bool_t          HLT_PFJet500;
   Bool_t          HLT_DiPFJetAve40;
   Bool_t          HLT_DiPFJetAve60;
   Bool_t          HLT_DiPFJetAve80;
   Bool_t          HLT_DiPFJetAve140;
   Bool_t          HLT_DiPFJetAve200;
   Bool_t          HLT_DiPFJetAve260;
   Bool_t          HLT_DiPFJetAve320;
   Bool_t          HLT_DiPFJetAve400;
   Bool_t          HLT_DiPFJetAve500;
   Bool_t          HLT_DiPFJetAve60_HFJEC;
   Bool_t          HLT_DiPFJetAve80_HFJEC;
   Bool_t          HLT_DiPFJetAve100_HFJEC;
   Bool_t          HLT_DiPFJetAve160_HFJEC;
   Bool_t          HLT_DiPFJetAve220_HFJEC;
   Bool_t          HLT_DiPFJetAve300_HFJEC;
   Bool_t          HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu140;
   Bool_t          HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu80;
   Bool_t          HLT_DiCentralPFJet170;
   Bool_t          HLT_SingleCentralPFJet170_CFMax0p1;
   Bool_t          HLT_DiCentralPFJet170_CFMax0p1;
   Bool_t          HLT_DiCentralPFJet220_CFMax0p3;
   Bool_t          HLT_DiCentralPFJet330_CFMax0p5;
   Bool_t          HLT_DiCentralPFJet430;
   Bool_t          HLT_PFHT125;
   Bool_t          HLT_PFHT200;
   Bool_t          HLT_PFHT250;
   Bool_t          HLT_PFHT300;
   Bool_t          HLT_PFHT350;
   Bool_t          HLT_PFHT400;
   Bool_t          HLT_PFHT475;
   Bool_t          HLT_PFHT600;
   Bool_t          HLT_PFHT650;
   Bool_t          HLT_PFHT800;
   Bool_t          HLT_PFHT900;
   Bool_t          HLT_PFHT200_PFAlphaT0p51;
   Bool_t          HLT_PFHT200_DiPFJetAve90_PFAlphaT0p57;
   Bool_t          HLT_PFHT200_DiPFJetAve90_PFAlphaT0p63;
   Bool_t          HLT_PFHT250_DiPFJetAve90_PFAlphaT0p55;
   Bool_t          HLT_PFHT250_DiPFJetAve90_PFAlphaT0p58;
   Bool_t          HLT_PFHT300_DiPFJetAve90_PFAlphaT0p53;
   Bool_t          HLT_PFHT300_DiPFJetAve90_PFAlphaT0p54;
   Bool_t          HLT_PFHT350_DiPFJetAve90_PFAlphaT0p52;
   Bool_t          HLT_PFHT350_DiPFJetAve90_PFAlphaT0p53;
   Bool_t          HLT_PFHT400_DiPFJetAve90_PFAlphaT0p51;
   Bool_t          HLT_PFHT400_DiPFJetAve90_PFAlphaT0p52;
   Bool_t          HLT_MET60_IsoTrk35_Loose;
   Bool_t          HLT_MET75_IsoTrk50;
   Bool_t          HLT_MET90_IsoTrk50;
   Bool_t          HLT_PFMET120_BTagCSV_p067;
   Bool_t          HLT_PFMET120_Mu5;
   Bool_t          HLT_PFMET170_NotCleaned;
   Bool_t          HLT_PFMET170_NoiseCleaned;
   Bool_t          HLT_PFMET170_HBHECleaned;
   Bool_t          HLT_PFMET170_JetIdCleaned;
   Bool_t          HLT_PFMET170_BeamHaloCleaned;
   Bool_t          HLT_PFMET170_HBHE_BeamHaloCleaned;
   Bool_t          HLT_PFMETTypeOne190_HBHE_BeamHaloCleaned;
   Bool_t          HLT_PFMET90_PFMHT90_IDTight;
   Bool_t          HLT_PFMET100_PFMHT100_IDTight;
   Bool_t          HLT_PFMET100_PFMHT100_IDTight_BeamHaloCleaned;
   Bool_t          HLT_PFMET110_PFMHT110_IDTight;
   Bool_t          HLT_PFMET120_PFMHT120_IDTight;
   Bool_t          HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV_p067;
   Bool_t          HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight;
   Bool_t          HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200;
   Bool_t          HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460;
   Bool_t          HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240;
   Bool_t          HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500;
   Bool_t          HLT_QuadPFJet_VBF;
   Bool_t          HLT_L1_TripleJet_VBF;
   Bool_t          HLT_QuadJet45_TripleBTagCSV_p087;
   Bool_t          HLT_QuadJet45_DoubleBTagCSV_p087;
   Bool_t          HLT_DoubleJet90_Double30_TripleBTagCSV_p087;
   Bool_t          HLT_DoubleJet90_Double30_DoubleBTagCSV_p087;
   Bool_t          HLT_DoubleJetsC100_DoubleBTagCSV_p026_DoublePFJetsC160;
   Bool_t          HLT_DoubleJetsC100_DoubleBTagCSV_p014_DoublePFJetsC100MaxDeta1p6;
   Bool_t          HLT_DoubleJetsC112_DoubleBTagCSV_p026_DoublePFJetsC172;
   Bool_t          HLT_DoubleJetsC112_DoubleBTagCSV_p014_DoublePFJetsC112MaxDeta1p6;
   Bool_t          HLT_DoubleJetsC100_SingleBTagCSV_p026;
   Bool_t          HLT_DoubleJetsC100_SingleBTagCSV_p014;
   Bool_t          HLT_DoubleJetsC100_SingleBTagCSV_p026_SinglePFJetC350;
   Bool_t          HLT_DoubleJetsC100_SingleBTagCSV_p014_SinglePFJetC350;
   Bool_t          HLT_Photon135_PFMET100;
   Bool_t          HLT_Photon20_CaloIdVL_IsoL;
   Bool_t          HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_PFMET40;
   Bool_t          HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_VBF;
   Bool_t          HLT_Photon250_NoHE;
   Bool_t          HLT_Photon300_NoHE;
   Bool_t          HLT_Photon26_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon16_AND_HE10_R9Id65_Eta2_Mass60;
   Bool_t          HLT_Photon36_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon22_AND_HE10_R9Id65_Eta2_Mass15;
   Bool_t          HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_PFMET40;
   Bool_t          HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_VBF;
   Bool_t          HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_PFMET40;
   Bool_t          HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_VBF;
   Bool_t          HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_PFMET40;
   Bool_t          HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_VBF;
   Bool_t          HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_PFMET40;
   Bool_t          HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_VBF;
   Bool_t          HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40;
   Bool_t          HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_VBF;
   Bool_t          HLT_Mu8_TrkIsoVVL;
   Bool_t          HLT_Mu17_TrkIsoVVL;
   Bool_t          HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30;
   Bool_t          HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30;
   Bool_t          HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30;
   Bool_t          HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30;
   Bool_t          HLT_BTagMu_DiJet20_Mu5;
   Bool_t          HLT_BTagMu_DiJet40_Mu5;
   Bool_t          HLT_BTagMu_DiJet70_Mu5;
   Bool_t          HLT_BTagMu_DiJet110_Mu5;
   Bool_t          HLT_BTagMu_DiJet170_Mu5;
   Bool_t          HLT_BTagMu_Jet300_Mu5;
   Bool_t          HLT_BTagMu_AK8Jet300_Mu5;
   Bool_t          HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded;
   Bool_t          HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL;
   Bool_t          HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL;
   Bool_t          HLT_Mu33_Ele33_CaloIdL_GsfTrkIdVL;
   Bool_t          HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL;
   Bool_t          HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL;
   Bool_t          HLT_Mu8_DiEle12_CaloIdL_TrackIdL;
   Bool_t          HLT_Mu12_Photon25_CaloIdL;
   Bool_t          HLT_Mu12_Photon25_CaloIdL_L1ISO;
   Bool_t          HLT_Mu12_Photon25_CaloIdL_L1OR;
   Bool_t          HLT_Mu17_Photon22_CaloIdL_L1ISO;
   Bool_t          HLT_Mu17_Photon30_CaloIdL_L1ISO;
   Bool_t          HLT_Mu17_Photon35_CaloIdL_L1ISO;
   Bool_t          HLT_DiMu9_Ele9_CaloIdL_TrackIdL;
   Bool_t          HLT_TripleMu_5_3_3;
   Bool_t          HLT_TripleMu_12_10_5;
   Bool_t          HLT_Mu3er_PFHT140_PFMET125;
   Bool_t          HLT_Mu6_PFHT200_PFMET80_BTagCSV_p067;
   Bool_t          HLT_Mu6_PFHT200_PFMET100;
   Bool_t          HLT_Mu14er_PFMET100;
   Bool_t          HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Ele12_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Ele17_CaloIdL_GsfTrkIdVL;
   Bool_t          HLT_Ele17_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Ele23_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_PFHT650_WideJetMJJ900DEtaJJ1p5;
   Bool_t          HLT_PFHT650_WideJetMJJ950DEtaJJ1p5;
   Bool_t          HLT_Photon22;
   Bool_t          HLT_Photon30;
   Bool_t          HLT_Photon36;
   Bool_t          HLT_Photon50;
   Bool_t          HLT_Photon75;
   Bool_t          HLT_Photon90;
   Bool_t          HLT_Photon120;
   Bool_t          HLT_Photon175;
   Bool_t          HLT_Photon165_HE10;
   Bool_t          HLT_Photon22_R9Id90_HE10_IsoM;
   Bool_t          HLT_Photon30_R9Id90_HE10_IsoM;
   Bool_t          HLT_Photon36_R9Id90_HE10_IsoM;
   Bool_t          HLT_Photon50_R9Id90_HE10_IsoM;
   Bool_t          HLT_Photon75_R9Id90_HE10_IsoM;
   Bool_t          HLT_Photon90_R9Id90_HE10_IsoM;
   Bool_t          HLT_Photon120_R9Id90_HE10_IsoM;
   Bool_t          HLT_Photon165_R9Id90_HE10_IsoM;
   Bool_t          HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90;
   Bool_t          HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelSeedMatch_Mass70;
   Bool_t          HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55;
   Bool_t          HLT_Diphoton30_18_Solid_R9Id_AND_IsoCaloId_AND_HE_R9Id_Mass55;
   Bool_t          HLT_Diphoton30EB_18EB_R9Id_OR_IsoCaloId_AND_HE_R9Id_DoublePixelVeto_Mass55;
   Bool_t          HLT_Dimuon0_Jpsi_Muon;
   Bool_t          HLT_Dimuon0_Upsilon_Muon;
   Bool_t          HLT_QuadMuon0_Dimuon0_Jpsi;
   Bool_t          HLT_QuadMuon0_Dimuon0_Upsilon;
   Bool_t          HLT_Rsq0p25_Calo;
   Bool_t          HLT_RsqMR240_Rsq0p09_MR200_4jet_Calo;
   Bool_t          HLT_RsqMR240_Rsq0p09_MR200_Calo;
   Bool_t          HLT_Rsq0p25;
   Bool_t          HLT_Rsq0p30;
   Bool_t          HLT_RsqMR240_Rsq0p09_MR200;
   Bool_t          HLT_RsqMR240_Rsq0p09_MR200_4jet;
   Bool_t          HLT_RsqMR270_Rsq0p09_MR200;
   Bool_t          HLT_RsqMR270_Rsq0p09_MR200_4jet;
   Bool_t          HLT_Rsq0p02_MR300_TriPFJet80_60_40_BTagCSV_p063_p20_Mbb60_200;
   Bool_t          HLT_Rsq0p02_MR400_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200;
   Bool_t          HLT_Rsq0p02_MR450_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200;
   Bool_t          HLT_Rsq0p02_MR500_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200;
   Bool_t          HLT_Rsq0p02_MR550_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200;
   Bool_t          HLT_HT200_DisplacedDijet40_DisplacedTrack;
   Bool_t          HLT_HT250_DisplacedDijet40_DisplacedTrack;
   Bool_t          HLT_HT350_DisplacedDijet40_DisplacedTrack;
   Bool_t          HLT_HT350_DisplacedDijet80_DisplacedTrack;
   Bool_t          HLT_HT350_DisplacedDijet80_Tight_DisplacedTrack;
   Bool_t          HLT_HT350_DisplacedDijet40_Inclusive;
   Bool_t          HLT_HT400_DisplacedDijet40_Inclusive;
   Bool_t          HLT_HT500_DisplacedDijet40_Inclusive;
   Bool_t          HLT_HT550_DisplacedDijet40_Inclusive;
   Bool_t          HLT_HT550_DisplacedDijet80_Inclusive;
   Bool_t          HLT_HT650_DisplacedDijet80_Inclusive;
   Bool_t          HLT_HT750_DisplacedDijet80_Inclusive;
   Bool_t          HLT_VBF_DisplacedJet40_DisplacedTrack;
   Bool_t          HLT_VBF_DisplacedJet40_DisplacedTrack_2TrackIP2DSig5;
   Bool_t          HLT_VBF_DisplacedJet40_TightID_DisplacedTrack;
   Bool_t          HLT_VBF_DisplacedJet40_Hadronic;
   Bool_t          HLT_VBF_DisplacedJet40_Hadronic_2PromptTrack;
   Bool_t          HLT_VBF_DisplacedJet40_TightID_Hadronic;
   Bool_t          HLT_VBF_DisplacedJet40_VTightID_Hadronic;
   Bool_t          HLT_VBF_DisplacedJet40_VVTightID_Hadronic;
   Bool_t          HLT_VBF_DisplacedJet40_VTightID_DisplacedTrack;
   Bool_t          HLT_VBF_DisplacedJet40_VVTightID_DisplacedTrack;
   Bool_t          HLT_PFMETNoMu90_PFMHTNoMu90_IDTight;
   Bool_t          HLT_PFMETNoMu100_PFMHTNoMu100_IDTight;
   Bool_t          HLT_PFMETNoMu110_PFMHTNoMu110_IDTight;
   Bool_t          HLT_PFMETNoMu120_PFMHTNoMu120_IDTight;
   Bool_t          HLT_MonoCentralPFJet80_PFMETNoMu90_PFMHTNoMu90_IDTight;
   Bool_t          HLT_MonoCentralPFJet80_PFMETNoMu100_PFMHTNoMu100_IDTight;
   Bool_t          HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight;
   Bool_t          HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight;
   Bool_t          HLT_Ele27_eta2p1_WPLoose_Gsf_HT200;
   Bool_t          HLT_Photon90_CaloIdL_PFHT500;
   Bool_t          HLT_DoubleMu8_Mass8_PFHT250;
   Bool_t          HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT250;
   Bool_t          HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT250;
   Bool_t          HLT_DoubleMu8_Mass8_PFHT300;
   Bool_t          HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300;
   Bool_t          HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300;
   Bool_t          HLT_Mu10_CentralPFJet30_BTagCSV_p13;
   Bool_t          HLT_DoubleMu3_PFMET50;
   Bool_t          HLT_Ele10_CaloIdM_TrackIdM_CentralPFJet30_BTagCSV_p13;
   Bool_t          HLT_Ele15_IsoVVVL_BTagCSV_p067_PFHT400;
   Bool_t          HLT_Ele15_IsoVVVL_PFHT350_PFMET50;
   Bool_t          HLT_Ele15_IsoVVVL_PFHT600;
   Bool_t          HLT_Ele15_IsoVVVL_PFHT350;
   Bool_t          HLT_Ele15_IsoVVVL_PFHT400_PFMET50;
   Bool_t          HLT_Ele15_IsoVVVL_PFHT400;
   Bool_t          HLT_Ele50_IsoVVVL_PFHT400;
   Bool_t          HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60;
   Bool_t          HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60;
   Bool_t          HLT_Mu15_IsoVVVL_BTagCSV_p067_PFHT400;
   Bool_t          HLT_Mu15_IsoVVVL_PFHT350_PFMET50;
   Bool_t          HLT_Mu15_IsoVVVL_PFHT600;
   Bool_t          HLT_Mu15_IsoVVVL_PFHT350;
   Bool_t          HLT_Mu15_IsoVVVL_PFHT400_PFMET50;
   Bool_t          HLT_Mu15_IsoVVVL_PFHT400;
   Bool_t          HLT_Mu50_IsoVVVL_PFHT400;
   Bool_t          HLT_Dimuon16_Jpsi;
   Bool_t          HLT_Dimuon10_Jpsi_Barrel;
   Bool_t          HLT_Dimuon8_PsiPrime_Barrel;
   Bool_t          HLT_Dimuon8_Upsilon_Barrel;
   Bool_t          HLT_Dimuon0_Phi_Barrel;
   Bool_t          HLT_Mu16_TkMu0_dEta18_Onia;
   Bool_t          HLT_Mu16_TkMu0_dEta18_Phi;
   Bool_t          HLT_TrkMu15_DoubleTrkMu5NoFiltersNoVtx;
   Bool_t          HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx;
   Bool_t          HLT_Mu8;
   Bool_t          HLT_Mu17;
   Bool_t          HLT_Mu3_PFJet40;
   Bool_t          HLT_Ele8_CaloIdM_TrackIdM_PFJet30;
   Bool_t          HLT_Ele12_CaloIdM_TrackIdM_PFJet30;
   Bool_t          HLT_Ele17_CaloIdM_TrackIdM_PFJet30;
   Bool_t          HLT_Ele23_CaloIdM_TrackIdM_PFJet30;
   Bool_t          HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet140;
   Bool_t          HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165;
   Bool_t          HLT_PFHT400_SixJet30_DoubleBTagCSV_p056;
   Bool_t          HLT_PFHT450_SixJet40_BTagCSV_p056;
   Bool_t          HLT_PFHT400_SixJet30;
   Bool_t          HLT_PFHT450_SixJet40;
   Bool_t          HLT_Ele115_CaloIdVT_GsfTrkIdT;
   Bool_t          HLT_Mu55;
   Bool_t          HLT_Photon42_R9Id85_OR_CaloId24b40e_Iso50T80L_Photon25_AND_HE10_R9Id65_Eta2_Mass15;
   Bool_t          HLT_Photon90_CaloIdL_PFHT600;
   Bool_t          HLT_PixelTracks_Multiplicity60ForEndOfFill;
   Bool_t          HLT_PixelTracks_Multiplicity85ForEndOfFill;
   Bool_t          HLT_PixelTracks_Multiplicity110ForEndOfFill;
   Bool_t          HLT_PixelTracks_Multiplicity135ForEndOfFill;
   Bool_t          HLT_PixelTracks_Multiplicity160ForEndOfFill;
   Bool_t          HLT_FullTracks_Multiplicity80;
   Bool_t          HLT_FullTracks_Multiplicity100;
   Bool_t          HLT_FullTracks_Multiplicity130;
   Bool_t          HLT_FullTracks_Multiplicity150;
   Bool_t          HLT_ECALHT800;
   Bool_t          HLT_DiSC30_18_EIso_AND_HE_Mass70;
   Bool_t          HLT_Photon125;
   Bool_t          HLT_MET100;
   Bool_t          HLT_MET150;
   Bool_t          HLT_MET200;
   Bool_t          HLT_Ele27_HighEta_Ele20_Mass55;
   Bool_t          HLT_L1FatEvents;
   Bool_t          HLT_Physics;
   Bool_t          HLT_L1FatEvents_part0;
   Bool_t          HLT_L1FatEvents_part1;
   Bool_t          HLT_L1FatEvents_part2;
   Bool_t          HLT_L1FatEvents_part3;
   Bool_t          HLT_Random;
   Bool_t          HLT_ZeroBias;
   Bool_t          HLT_AK4CaloJet30;
   Bool_t          HLT_AK4CaloJet40;
   Bool_t          HLT_AK4CaloJet50;
   Bool_t          HLT_AK4CaloJet80;
   Bool_t          HLT_AK4CaloJet100;
   Bool_t          HLT_AK4PFJet30;
   Bool_t          HLT_AK4PFJet50;
   Bool_t          HLT_AK4PFJet80;
   Bool_t          HLT_AK4PFJet100;
   Bool_t          HLT_HISinglePhoton10;
   Bool_t          HLT_HISinglePhoton15;
   Bool_t          HLT_HISinglePhoton20;
   Bool_t          HLT_HISinglePhoton40;
   Bool_t          HLT_HISinglePhoton60;
   Bool_t          HLT_EcalCalibration;
   Bool_t          HLT_HcalCalibration;
   Bool_t          HLT_GlobalRunHPDNoise;
   Bool_t          HLT_L1BptxMinus;
   Bool_t          HLT_L1BptxPlus;
   Bool_t          HLT_L1NotBptxOR;
   Bool_t          HLT_L1BeamGasMinus;
   Bool_t          HLT_L1BeamGasPlus;
   Bool_t          HLT_L1BptxXOR;
   Bool_t          HLT_L1MinimumBiasHF_OR;
   Bool_t          HLT_L1MinimumBiasHF_AND;
   Bool_t          HLT_HcalNZS;
   Bool_t          HLT_HcalPhiSym;
   Bool_t          HLT_HcalIsolatedbunch;
   Bool_t          HLT_ZeroBias_FirstCollisionAfterAbortGap;
   Bool_t          HLT_ZeroBias_FirstCollisionAfterAbortGap_copy;
   Bool_t          HLT_ZeroBias_FirstCollisionAfterAbortGap_TCDS;
   Bool_t          HLT_ZeroBias_IsolatedBunches;
   Bool_t          HLT_ZeroBias_FirstCollisionInTrain;
   Bool_t          HLT_ZeroBias_FirstBXAfterTrain;
   Bool_t          HLT_Photon500;
   Bool_t          HLT_Photon600;
   Bool_t          HLT_Mu300;
   Bool_t          HLT_Mu350;
   Bool_t          HLT_MET250;
   Bool_t          HLT_MET300;
   Bool_t          HLT_MET600;
   Bool_t          HLT_MET700;
   Bool_t          HLT_PFMET300;
   Bool_t          HLT_PFMET400;
   Bool_t          HLT_PFMET500;
   Bool_t          HLT_PFMET600;
   Bool_t          HLT_Ele250_CaloIdVT_GsfTrkIdT;
   Bool_t          HLT_Ele300_CaloIdVT_GsfTrkIdT;
   Bool_t          HLT_HT2000;
   Bool_t          HLT_HT2500;
   Bool_t          HLT_IsoTrackHE;
   Bool_t          HLT_IsoTrackHB;
   Bool_t          HLTriggerFinalPath;
