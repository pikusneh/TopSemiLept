#include <ROOT/RDataFrame.hxx>
#include <TCanvas.h>
#include <TH1D.h>

void hist() {
    
    // std::string fileName = "/eos/uscms/store/user/snehshuc/test/2017/TTGamma_Hadronic.root";
    std::string fileName = " /eos/uscms/store/user/snehshuc/test/2017/analyzed/TTGamma_Hadronic_output.root";
   
    std::string treeName = "outputTree2"; 
    ROOT::RDataFrame df(treeName, fileName);

    // auto df1 = df.Define("weight","btag_SF_central * ele_SF_central * muon_SF_central * evWeight ");
    auto hist_evWeight = df.Histo1D({"evWeight","evWeight;X-axis;Yaxis",6,0,3},"evWeight");
    auto hist_NtightElectrons = df.Histo1D({"NtightElectrons", "NtightElectrons;X-axis;Y-axis", 6, 0, 3}, "NtightElectrons");
    auto hist_tightElectrons_pt_noweight = df.Histo1D({"tightElectrons_pt_noweight","tightElectrons_pt_noweight;X-axis;Y-axis",25, 0, 250}, "tightElectrons_pt");
    auto hist_tightElectrons_pt = df.Histo1D({"tightElectrons_pt", "tightElectrons_pt;X-axis;Y-axis",  25, 0, 250}, "tightElectrons_pt","evWeight");
    
    TFile *f = new TFile("hist1.root","RECREATE");

    hist_NtightElectrons->Write();
    hist_tightElectrons_pt->Write();
    hist_tightElectrons_pt_noweight->Write();
    hist_evWeight->Write();

   
    f->Close();
}