#include <ROOT/RDataFrame.hxx>
#include <TCanvas.h>
#include <TH1D.h>

void hist() {
    
    std::string fileName = "/eos/uscms/store/user/snehshuc/test/2017/TTGamma_output.root";
    std::string treeName = "outputTree2"; 
    ROOT::RDataFrame df(treeName, fileName);

    auto df1 = df.Define("weight","btag_SF_central * ele_SF_central * muon_SF_central ");
    auto hist = df1.Histo1D({"Electron_pt", "elept;X-axis;Y-axis", 25, 0, 250}, "goodElectrons_pt");
    auto hist_weight = df1.Histo1D({"Electron_pt_with_weight", "elept;X-axis;Y-axis", 25, 0, 250}, "goodElectrons_pt", "weight");
    hist->Draw("hist");
    hist_weight->Draw("hist");
    TCanvas *c = new TCanvas("c","c",800,800);
    c->cd();
    hist_weight->Draw("hist ");
    hist_weight->SetLineColor(kBlue);
    hist->Draw("hist same");
    hist->SetLineColor(kRed);

    TFile *f = new TFile("hist.root","RECREATE");
    hist->Write();
    hist_weight->Write();
    c->Write();
    f->Close();
}