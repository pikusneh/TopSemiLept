#include <ROOT/RDataFrame.hxx>
#include <TCanvas.h>
#include <TH1D.h>

void hist() {
    
    std::string fileName = "/eos/uscms/store/user/snehshuc/test/2017/TTGamma_output_100k.root";
    std::string treeName = "outputTree2"; 
    ROOT::RDataFrame df(treeName, fileName);

    auto df1 = df.Define("weight","btag_SF_central * ele_SF_central * muon_SF_central ");
    auto hist_ele = df1.Histo1D({"Electron_pt", "elept;X-axis;Y-axis", 25, 0, 250}, "tightElectrons_pt");
    auto hist_weight_ele = df1.Histo1D({"Electron_pt_with_weight", "elept;X-axis;Y-axis", 25, 0, 250}, "tightElectrons_pt", "weight");
    auto hist_muon = df1.Histo1D({"Muon_pt", "muonpt;X-axis;Y-axis", 25, 0, 250}, "tightMuons_pt");
    auto hist_weight_muon = df1.Histo1D({"Muon_pt_with_weight", "muonpt;X-axis;Y-axis", 25, 0, 250}, "tightMuons_pt", "weight");
    auto hist_run = df.Histo1D({"run", "run;X-axis;Y-axis", 100, 0, 2}, "run");
    auto hist_NtightElectrons = df.Histo1D({"NtightElectrons", "NtightElectrons;X-axis;Y-axis", 6, 0, 3}, "NtightElectrons");
    hist_ele->Draw("hist");
    hist_weight_ele->Draw("hist");
    TCanvas *c = new TCanvas("c","c",800,800);
    c->cd();
    hist_weight_ele->Draw("hist");
    hist_weight_ele->SetLineColor(kBlue);
    hist_ele->Draw("hist same");
    hist_ele->SetLineColor(kRed);

    TFile *f = new TFile("hist.root","RECREATE");
    hist_ele->Write();
    hist_weight_ele->Write();
    hist_run->Write();
    hist_NtightElectrons->Write();
    hist_muon->Write();
    hist_weight_muon->Write();
    c->Write();
    f->Close();
}