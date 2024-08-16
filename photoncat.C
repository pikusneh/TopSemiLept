#include <ROOT/RDataFrame.hxx>
#include <TCanvas.h>
#include <TH1D.h>

void photoncat() {
    
    std::vector<std::string> TTgamma = {"/eos/uscms/store/user/snehshuc/test/2017/TTGamma_Dilept.root",
    "/eos/uscms/store/user/snehshuc/test/2017/TTGamma_Hadronic.root",
    "/eos/uscms/store/user/snehshuc/test/2017/TTGamma_Semilept.root"};
    std::string treeName = "outputTree2"; 

    std::vector<std::string> TTbar = {"/eos/uscms/store/user/snehshuc/test/2017/TTbar_Hadronic_300.root",
    "/eos/uscms/store/user/snehshuc/test/2017/TTbar_Dilept_300.root"};
    ROOT::RDataFrame df(treeName, TTgamma);
    ROOT::RDataFrame df_TTbar(treeName, TTbar);

    auto df_muon = df.Filter("NtightMuons == 1");
    auto df_muon_TTbar = df_TTbar.Filter("NtightMuons == 1");
    auto df_electron = df.Filter("NtightElectrons == 1");
    auto df_electron_TTbar = df_TTbar.Filter("NtightElectrons == 1");
    // number of events after muon channel selection
    auto df_muon_ch = df_muon.Count();
    std::cout << "Number of events after muon channel selection in TTGamma sample: " << *df_muon_ch << std::endl;
    auto df_muon_ch_TTbar = df_muon_TTbar.Count();
    std::cout << "Number of events after muon channel selection in TTbar sample: " << *df_muon_ch_TTbar << std::endl;
    // number of events after electron channel selection
    auto df_electron_ch = df_electron.Count();
    std::cout << "Number of events after electron channel selection in TTGamma sample: " << *df_electron_ch << std::endl;
    auto df_electron_ch_TTbar = df_electron_TTbar.Count();
    std::cout << "Number of events after electron channel selection in TTbar sample: " << *df_electron_ch_TTbar << std::endl;

    auto df_photon = df_muon.Filter("NgoodPhotons == 1");
    auto df_photon_TTbar = df_muon_TTbar.Filter("NgoodPhotons == 1");
    //print number of events after photon selection
    auto df_photon_ch = df_photon.Count();
    std::cout << "Number of events after photon selection in TTGamma sample : " << *df_photon_ch << std::endl;
    auto df_photon_ch_TTbar = df_photon_TTbar.Count();
    std::cout << "Number of events after photon selection in TTbar sample : " << *df_photon_ch_TTbar << std::endl;

    auto df_pho_isgenuine = df_photon.Filter("_photonIsGenuine[0] == 1");
    auto df_pho_ishadronic = df_photon.Filter("_photonIsHadronicPhoton[0] == 1");
    auto df_pho_ismisid = df_photon.Filter("_photonIsMisIDEle[0] == 1");
    auto df_pho_ishadronicfake = df_photon.Filter("_photonIsHadronicFake[0] == 1");

    auto df_pho_isgenuine_TTbar = df_photon_TTbar.Filter("_photonIsGenuine[0] == 1");
    auto df_pho_ishadronic_TTbar = df_photon_TTbar.Filter("_photonIsHadronicPhoton[0] == 1");
    auto df_pho_ismisid_TTbar = df_photon_TTbar.Filter("_photonIsMisIDEle[0] == 1");
    auto df_pho_ishadronicfake_TTbar = df_photon_TTbar.Filter("_photonIsHadronicFake[0] == 1");

    // Define histograms for each photon category
    auto h_pho_isgenuine = df_pho_isgenuine.Histo1D({"h_pho_isgenuine", "Genuine Photon", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ishadronic = df_pho_ishadronic.Histo1D({"h_pho_ishadronic", "Hadronic Photon", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ismisid = df_pho_ismisid.Histo1D({"h_pho_ismisid", "MisID Photon", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ishadronicfake = df_pho_ishadronicfake.Histo1D({"h_pho_ishadronicfake", "Hadronic Fake Photon", 50, 0, 200}, "goodPhotons_pt");

    auto h_pho_isgenuine_TTbar = df_pho_isgenuine_TTbar.Histo1D({"h_pho_isgenuine_TTbar", "Genuine Photon", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ishadronic_TTbar = df_pho_ishadronic_TTbar.Histo1D({"h_pho_ishadronic_TTbar", "Hadronic Photon", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ismisid_TTbar = df_pho_ismisid_TTbar.Histo1D({"h_pho_ismisid_TTbar", "MisID Photon", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ishadronicfake_TTbar = df_pho_ishadronicfake_TTbar.Histo1D({"h_pho_ishadronicfake_TTbar", "Hadronic Fake Photon", 50, 0, 200}, "goodPhotons_pt");

    auto hist_tightElectrons_pt = df.Histo1D({"tightElectrons_pt", "tightElectrons_pt;X-axis;Y-axis",  25, 0, 250}, "tightElectrons_pt","evWeight");

    auto hist_goodPhotons_pt = df_photon.Histo1D({"goodPhotons_pt", "goodPhotons_pt;X-axis;Y-axis",  25, 0, 250}, "goodPhotons_pt");

    auto hist_tightElectrons_pt_TTbar = df_TTbar.Histo1D({"tightElectrons_pt_TTbar", "tightElectrons_pt_TTbar;X-axis;Y-axis",  25, 0, 250}, "tightElectrons_pt","evWeight");

    auto hist_goodPhotons_pt_TTbar = df_photon_TTbar.Histo1D({"goodPhotons_pt_TTbar", "goodPhotons_pt_TTbar;X-axis;Y-axis",  25, 0, 250}, "goodPhotons_pt");
    
    // Create a canvas to draw the histograms
    TCanvas c1("c1", "Photon Categories", 800, 600);
    THStack hs("hs", "Stacked Photon Categories");

    // Set colors for each histogram
    h_pho_isgenuine->SetFillColor(kBlue);
    h_pho_ishadronic->SetFillColor(kRed);
    h_pho_ismisid->SetFillColor(kGreen);
    h_pho_ishadronicfake->SetFillColor(kMagenta);

    // Add histograms to the stack
    hs.Add(h_pho_isgenuine.GetPtr());
    hs.Add(h_pho_ishadronic.GetPtr());
    hs.Add(h_pho_ismisid.GetPtr());
    hs.Add(h_pho_ishadronicfake.GetPtr());

    // Draw the stacked histograms
    hs.Draw("HIST");

    // Add a legend
    TLegend legend(0.7, 0.7, 0.9, 0.9);
    legend.AddEntry(h_pho_isgenuine.GetPtr(), "Genuine Photon", "f");
    legend.AddEntry(h_pho_ishadronic.GetPtr(), "Hadronic Photon", "f");
    legend.AddEntry(h_pho_ismisid.GetPtr(), "MisID Photon", "f");
    legend.AddEntry(h_pho_ishadronicfake.GetPtr(), "Hadronic Fake Photon", "f");
    legend.Draw();

//TTbar sample Canvas and histograms
    TCanvas c2("c2", "Photon Categories TTbar", 800, 600);
    THStack hs_TTbar("hs_TTbar", "Stacked Photon Categories TTbar");

    h_pho_isgenuine_TTbar->SetFillColor(kBlue);
    h_pho_ishadronic_TTbar->SetFillColor(kRed);
    h_pho_ismisid_TTbar->SetFillColor(kGreen);
    h_pho_ishadronicfake_TTbar->SetFillColor(kMagenta);

    hs_TTbar.Add(h_pho_isgenuine_TTbar.GetPtr());
    hs_TTbar.Add(h_pho_ishadronic_TTbar.GetPtr());
    hs_TTbar.Add(h_pho_ismisid_TTbar.GetPtr());
    hs_TTbar.Add(h_pho_ishadronicfake_TTbar.GetPtr());

    hs_TTbar.Draw("HIST");

    TLegend legend_TTbar(0.7, 0.7, 0.9, 0.9);
    legend_TTbar.AddEntry(h_pho_isgenuine_TTbar.GetPtr(), "Genuine Photon", "f");
    legend_TTbar.AddEntry(h_pho_ishadronic_TTbar.GetPtr(), "Hadronic Photon", "f");
    legend_TTbar.AddEntry(h_pho_ismisid_TTbar.GetPtr(), "MisID Photon", "f");
    legend_TTbar.AddEntry(h_pho_ishadronicfake_TTbar.GetPtr(), "Hadronic Fake Photon", "f");
    legend_TTbar.Draw();
    
    TFile *f = new TFile("photon_cat.root","RECREATE");

    hist_tightElectrons_pt->Write();
    h_pho_isgenuine->Write();
    h_pho_ishadronic->Write();
    h_pho_ismisid->Write();
    h_pho_ishadronicfake->Write();
    hist_goodPhotons_pt->Write();
    h_pho_isgenuine_TTbar->Write();
    h_pho_ishadronic_TTbar->Write();
    h_pho_ismisid_TTbar->Write();
    h_pho_ishadronicfake_TTbar->Write();
    hist_tightElectrons_pt_TTbar->Write();
    hist_goodPhotons_pt_TTbar->Write();
    c1.Write();
    c2.Write();

   
    f->Close();
}
