#include <ROOT/RDataFrame.hxx>
#include <TCanvas.h>
#include <TH1D.h>

void photoncat() {
    
    std::vector<std::string> TTgamma = {"/eos/uscms/store/user/snehshuc/test/2017/TTGamma_Dilept_new.root",
    "/eos/uscms/store/user/snehshuc/test/2017/TTGamma_Hadronic_new.root",
    "/eos/uscms/store/user/snehshuc/test/2017/TTGamma_Semilept_new.root"};
    std::string treeName = "outputTree2"; 

    std::vector<std::string> TTbar = {"/eos/uscms/store/user/snehshuc/test/2017/TTbar_Hadronic_300.root",
    "/eos/uscms/store/user/snehshuc/test/2017/TTbar_Dilept_300.root",
    "/eos/uscms/store/user/snehshuc/test/2017/TTbar_Semilept_300.root"};
    
    ROOT::RDataFrame df1(treeName, TTgamma);
    ROOT::RDataFrame df2(treeName, TTbar);
    
    //number of events in TTGamma and TTbar
    auto df_TTGamma = df1.Count();
    std::cout << "Number of events in TTGamma sample: " << *df_TTGamma << std::endl;
    auto df_TTBar = df2.Count();
    std::cout << "Number of events in TTbar sample: " << *df_TTBar << std::endl;

// --------------------------------muon channel selection-------------------------------------------------------------------------------------------
    auto df_muon_TTGamma = df1.Filter("NtightMuons == 1 && NgoodJets >= 3");
    auto df_muon_TTbar = df2.Filter("NtightMuons == 1 && NgoodJets >= 3");
    // number of events after muon channel selection
    auto df_muon_ch_TTGamma = df_muon_TTGamma.Count();
    std::cout << "Number of events after muon channel and Jets selection in TTGamma sample: " << *df_muon_ch_TTGamma << std::endl;
    auto df_muon_ch_TTbar = df_muon_TTbar.Count();
    std::cout << "Number of events after muon channel and Jets selection in TTbar sample: " << *df_muon_ch_TTbar << std::endl;

    auto df_photon_muon_TTGamma = df_muon_TTGamma.Filter("NgoodPhotons == 1 ");  
    auto df_photon_muon_TTbar = df_muon_TTbar.Filter("NgoodPhotons == 1");
    // number of events after photon selection
    auto df_photon_ch_muon_TTGamma = df_photon_muon_TTGamma.Count();
    std::cout << "Number of events after photon selection in TTGamma sample : " << *df_photon_ch_muon_TTGamma << std::endl;
    auto df_photon_ch_muon_TTbar = df_photon_muon_TTbar.Count();
    std::cout << "Number of events after photon selection in TTbar sample : " << *df_photon_ch_muon_TTbar << std::endl;

    auto df_pho_isgenuine_muon_TTGamma = df_photon_muon_TTGamma.Filter("_photonIsGenuine[0] == 1");
    auto df_pho_ishadronic_muon_TTGamma = df_photon_muon_TTGamma.Filter("_photonIsHadronicPhoton[0] == 1");
    auto df_pho_ismisid_muon_TTGamma = df_photon_muon_TTGamma.Filter("_photonIsMisIDEle[0] == 1");
    auto df_pho_ishadronicfake_muon_TTGamma = df_photon_muon_TTGamma.Filter("_photonIsHadronicFake[0] == 1");

    auto df_pho_isgenuine_muon_TTbar = df_photon_muon_TTbar.Filter("_photonIsGenuine[0] == 1");
    auto df_pho_ishadronic_muon_TTbar = df_photon_muon_TTbar.Filter("_photonIsHadronicPhoton[0] == 1");
    auto df_pho_ismisid_muon_TTbar = df_photon_muon_TTbar.Filter("_photonIsMisIDEle[0] == 1");
    auto df_pho_ishadronicfake_muon_TTbar = df_photon_muon_TTbar.Filter("_photonIsHadronicFake[0] == 1");

    auto h_pho_isgenuine_muon_TTGamma = df_pho_isgenuine_muon_TTGamma.Histo1D({"h_pho_isgenuine_muon_TTGamma", "Genuine Photon (tt + #gamma), muon channel", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ishadronic_muon_TTGamma = df_pho_ishadronic_muon_TTGamma.Histo1D({"h_pho_ishadronic_muon_TTGamma", "Hadronic Photon (tt + #gamma), muon channel", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ismisid_muon_TTGamma = df_pho_ismisid_muon_TTGamma.Histo1D({"h_pho_ismisid_muon_TTGamma", "MisID Photon (tt + #gamma), muon channel", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ishadronicfake_muon_TTGamma = df_pho_ishadronicfake_muon_TTGamma.Histo1D({"h_pho_ishadronicfake_muon_TTGamma", "Hadronic Fake Photon (tt + #gamma), muon channel", 50, 0, 200}, "goodPhotons_pt");

    auto h_pho_isgenuine_muon_TTbar = df_pho_isgenuine_muon_TTbar.Histo1D({"h_pho_isgenuine_muon_TTbar", "Genuine Photon (tt), muon channel", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ishadronic_muon_TTbar = df_pho_ishadronic_muon_TTbar.Histo1D({"h_pho_ishadronic_muon_TTbar", "Hadronic Photon (tt), muon channel", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ismisid_muon_TTbar = df_pho_ismisid_muon_TTbar.Histo1D({"h_pho_ismisid_muon_TTbar", "MisID Photon (tt), muon channel", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ishadronicfake_muon_TTbar = df_pho_ishadronicfake_muon_TTbar.Histo1D({"h_pho_ishadronicfake_muon_TTbar", "Hadronic Fake Photon (tt), muon channel", 50, 0, 200}, "goodPhotons_pt");


    // --------------------------------electron channel selection-------------------------------------------------------------------------------------------
    auto df_electron_TTgamma = df1.Filter("NtightElectrons == 1 && NgoodJets >= 3");
    auto df_electron_TTbar = df2.Filter("NtightElectrons == 1 && NgoodJets >= 3");
    // number of evWeightents after electron channel selection
    auto df_electron_ch_TTGamma = df_electron_TTgamma.Count();
    std::cout << "Number of events after electron channel and Jets selection in TTGamma sample: " << *df_electron_ch_TTGamma << std::endl;
    auto df_electron_ch_TTbar = df_electron_TTbar.Count();
    std::cout << "Number of events after electron channel and Jets selection in TTbar sample: " << *df_electron_ch_TTbar << std::endl;

    auto df_photon_electron_TTGamma = df_electron_TTgamma.Filter("NgoodPhotons == 1");
    auto df_photon_electron_TTbar = df_electron_TTbar.Filter("NgoodPhotons == 1");
    // number of events after photon selection
    auto df_photon_ch_electron_TTGamma = df_photon_electron_TTGamma.Count();
    std::cout << "Number of events after photon selection in TTGamma sample : " << *df_photon_ch_electron_TTGamma << std::endl;
    auto df_photon_ch_electron_TTbar = df_photon_electron_TTbar.Count();
    std::cout << "Number of events after photon selection in TTbar sample : " << *df_photon_ch_electron_TTbar << std::endl;

    auto df_pho_isgenuine_electron_TTGamma = df_photon_electron_TTGamma.Filter("_photonIsGenuine[0] == 1");
    auto df_pho_ishadronic_electron_TTGamma = df_photon_electron_TTGamma.Filter("_photonIsHadronicPhoton[0] == 1");
    auto df_pho_ismisid_electron_TTGamma = df_photon_electron_TTGamma.Filter("_photonIsMisIDEle[0] == 1");
    auto df_pho_ishadronicfake_electron_TTGamma = df_photon_electron_TTGamma.Filter("_photonIsHadronicFake[0] == 1");

    auto df_pho_isgenuine_electron_TTbar = df_photon_electron_TTbar.Filter("_photonIsGenuine[0] == 1");
    auto df_pho_ishadronic_electron_TTbar = df_photon_electron_TTbar.Filter("_photonIsHadronicPhoton[0] == 1");
    auto df_pho_ismisid_electron_TTbar = df_photon_electron_TTbar.Filter("_photonIsMisIDEle[0] == 1");
    auto df_pho_ishadronicfake_electron_TTbar = df_photon_electron_TTbar.Filter("_photonIsHadronicFake[0] == 1");

    auto h_pho_isgenuine_electron_TTGamma = df_pho_isgenuine_electron_TTGamma.Histo1D({"h_pho_isgenuine_electron_TTGamma", "Genuine Photon (tt + #gamma), electron channel", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ishadronic_electron_TTGamma = df_pho_ishadronic_electron_TTGamma.Histo1D({"h_pho_ishadronic_electron_TTGamma", "Hadronic Photon (tt + #gamma), electron channel", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ismisid_electron_TTGamma = df_pho_ismisid_electron_TTGamma.Histo1D({"h_pho_ismisid_electron_TTGamma", "MisID Photon (tt + #gamma), electron channel", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ishadronicfake_electron_TTGamma = df_pho_ishadronicfake_electron_TTGamma.Histo1D({"h_pho_ishadronicfake_electron_TTGamma", "Hadronic Fake Photon (tt + #gamma), electron channel", 50, 0, 200}, "goodPhotons_pt");

    auto h_pho_isgenuine_electron_TTbar = df_pho_isgenuine_electron_TTbar.Histo1D({"h_pho_isgenuine_electron_TTbar", "Genuine Photon (tt), electron channel", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ishadronic_electron_TTbar = df_pho_ishadronic_electron_TTbar.Histo1D({"h_pho_ishadronic_electron_TTbar", "Hadronic Photon (tt), electron channel", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ismisid_electron_TTbar = df_pho_ismisid_electron_TTbar.Histo1D({"h_pho_ismisid_electron_TTbar", "MisID Photon (tt), electron channel", 50, 0, 200}, "goodPhotons_pt");
    auto h_pho_ishadronicfake_electron_TTbar = df_pho_ishadronicfake_electron_TTbar.Histo1D({"h_pho_ishadronicfake_electron_TTbar", "Hadronic Fake Photon (tt), electron channel", 50, 0, 200}, "goodPhotons_pt");

// ---------------------------------------------------------Canvas-----------------------------------------------------------
    // Create a canvas to draw the histograms
    TCanvas c1_muon_TTGamma("c1_muon_TTGamma", "Photon Categories", 800, 600);
    THStack hs_muon_TTGamma("hs_muon_TTGamma", "Photon Categories (tt + #gamma) muon channel");
    h_pho_isgenuine_muon_TTGamma->SetFillColor(kBlue);
    h_pho_ishadronic_muon_TTGamma->SetFillColor(kRed);
    h_pho_ismisid_muon_TTGamma->SetFillColor(kGreen);
    h_pho_ishadronicfake_muon_TTGamma->SetFillColor(kMagenta);

    hs_muon_TTGamma.Add(h_pho_isgenuine_muon_TTGamma.GetPtr());
    hs_muon_TTGamma.Add(h_pho_ishadronic_muon_TTGamma.GetPtr());
    hs_muon_TTGamma.Add(h_pho_ismisid_muon_TTGamma.GetPtr());
    hs_muon_TTGamma.Add(h_pho_ishadronicfake_muon_TTGamma.GetPtr());

    hs_muon_TTGamma.Draw("HIST");

    TLegend legend_muon_TTGamma(0.7, 0.7, 0.9, 0.9);
    legend_muon_TTGamma.AddEntry(h_pho_isgenuine_muon_TTGamma.GetPtr(), "Genuine Photon", "f");
    legend_muon_TTGamma.AddEntry(h_pho_ishadronic_muon_TTGamma.GetPtr(), "Hadronic Photon", "f");
    legend_muon_TTGamma.AddEntry(h_pho_ismisid_muon_TTGamma.GetPtr(), "MisID Photon", "f");
    legend_muon_TTGamma.AddEntry(h_pho_ishadronicfake_muon_TTGamma.GetPtr(), "Hadronic Fake Photon", "f");
    legend_muon_TTGamma.Draw();

    TCanvas c2_muon_TTbar("c2_muon_TTbar", "Photon Categories TTbar", 800, 600);
    THStack hs_muon_TTbar("hs_muon_TTbar", "Photon Categories TTbar muon channel");

    h_pho_isgenuine_muon_TTbar->SetFillColor(kBlue);
    h_pho_ishadronic_muon_TTbar->SetFillColor(kRed);
    h_pho_ismisid_muon_TTbar->SetFillColor(kGreen);
    h_pho_ishadronicfake_muon_TTbar->SetFillColor(kMagenta);

    hs_muon_TTbar.Add(h_pho_isgenuine_muon_TTbar.GetPtr());
    hs_muon_TTbar.Add(h_pho_ishadronic_muon_TTbar.GetPtr());
    hs_muon_TTbar.Add(h_pho_ismisid_muon_TTbar.GetPtr());
    hs_muon_TTbar.Add(h_pho_ishadronicfake_muon_TTbar.GetPtr());

    hs_muon_TTbar.Draw("HIST");

    TLegend legend_muon_TTbar(0.7, 0.7, 0.9, 0.9);
    legend_muon_TTbar.AddEntry(h_pho_isgenuine_muon_TTbar.GetPtr(), "Genuine Photon", "f");
    legend_muon_TTbar.AddEntry(h_pho_ishadronic_muon_TTbar.GetPtr(), "Hadronic Photon", "f");
    legend_muon_TTbar.AddEntry(h_pho_ismisid_muon_TTbar.GetPtr(), "MisID Photon", "f");
    legend_muon_TTbar.AddEntry(h_pho_ishadronicfake_muon_TTbar.GetPtr(), "Hadronic Fake Photon", "f");
    legend_muon_TTbar.Draw();

    TCanvas c1_electron_TTGamma("c1_electron_TTGamma", "Photon Categories", 800, 600);
    THStack hs_electron_TTGamma("hs_electron_TTGamma", "Photon Categories (tt + #gamma) electron channel");

    h_pho_isgenuine_electron_TTGamma->SetFillColor(kBlue);
    h_pho_ishadronic_electron_TTGamma->SetFillColor(kRed);
    h_pho_ismisid_electron_TTGamma->SetFillColor(kGreen);
    h_pho_ishadronicfake_electron_TTGamma->SetFillColor(kMagenta);

    hs_electron_TTGamma.Add(h_pho_isgenuine_electron_TTGamma.GetPtr());
    hs_electron_TTGamma.Add(h_pho_ishadronic_electron_TTGamma.GetPtr());
    hs_electron_TTGamma.Add(h_pho_ismisid_electron_TTGamma.GetPtr());
    hs_electron_TTGamma.Add(h_pho_ishadronicfake_electron_TTGamma.GetPtr());

    hs_electron_TTGamma.Draw("HIST");

    TLegend legend_electron_TTGamma(0.7, 0.7, 0.9, 0.9);
    legend_electron_TTGamma.AddEntry(h_pho_isgenuine_electron_TTGamma.GetPtr(), "Genuine Photon", "f");
    legend_electron_TTGamma.AddEntry(h_pho_ishadronic_electron_TTGamma.GetPtr(), "Hadronic Photon", "f");
    legend_electron_TTGamma.AddEntry(h_pho_ismisid_electron_TTGamma.GetPtr(), "MisID Photon", "f");
    legend_electron_TTGamma.AddEntry(h_pho_ishadronicfake_electron_TTGamma.GetPtr(), "Hadronic Fake Photon", "f");

    legend_electron_TTGamma.Draw();

    TCanvas c2_electron_TTbar("c2_electron_TTbar", "Photon Categories TTbar", 800, 600);
    THStack hs_electron_TTbar("hs_electron_TTbar", "Photon Categories TTbar electron channel");

    h_pho_isgenuine_electron_TTbar->SetFillColor(kBlue);
    h_pho_ishadronic_electron_TTbar->SetFillColor(kRed);
    h_pho_ismisid_electron_TTbar->SetFillColor(kGreen);
    h_pho_ishadronicfake_electron_TTbar->SetFillColor(kMagenta);

    hs_electron_TTbar.Add(h_pho_isgenuine_electron_TTbar.GetPtr());
    hs_electron_TTbar.Add(h_pho_ishadronic_electron_TTbar.GetPtr());
    hs_electron_TTbar.Add(h_pho_ismisid_electron_TTbar.GetPtr());
    hs_electron_TTbar.Add(h_pho_ishadronicfake_electron_TTbar.GetPtr());

    hs_electron_TTbar.Draw("HIST");

    TLegend legend_electron_TTbar(0.7, 0.7, 0.9, 0.9);
    legend_electron_TTbar.AddEntry(h_pho_isgenuine_electron_TTbar.GetPtr(), "Genuine Photon", "f");
    legend_electron_TTbar.AddEntry(h_pho_ishadronic_electron_TTbar.GetPtr(), "Hadronic Photon", "f");
    legend_electron_TTbar.AddEntry(h_pho_ismisid_electron_TTbar.GetPtr(), "MisID Photon", "f");
    legend_electron_TTbar.AddEntry(h_pho_ishadronicfake_electron_TTbar.GetPtr(), "Hadronic Fake Photon", "f");

    legend_electron_TTbar.Draw();

    
    TFile *f = new TFile("photon_categoryWeight.root","RECREATE");

    h_pho_isgenuine_muon_TTGamma->Write();
    h_pho_ishadronic_muon_TTGamma->Write();
    h_pho_ismisid_muon_TTGamma->Write();
    h_pho_ishadronicfake_muon_TTGamma->Write();
    h_pho_isgenuine_muon_TTbar->Write();
    h_pho_ishadronic_muon_TTbar->Write();
    h_pho_ismisid_muon_TTbar->Write();
    h_pho_ishadronicfake_muon_TTbar->Write();
    h_pho_isgenuine_electron_TTGamma->Write();
    h_pho_ishadronic_electron_TTGamma->Write();
    h_pho_ismisid_electron_TTGamma->Write();
    h_pho_ishadronicfake_electron_TTGamma->Write();
    h_pho_isgenuine_electron_TTbar->Write();
    h_pho_ishadronic_electron_TTbar->Write();
    h_pho_ismisid_electron_TTbar->Write();
    h_pho_ishadronicfake_electron_TTbar->Write();

    c1_muon_TTGamma.Write();
    c2_muon_TTbar.Write();
    c1_electron_TTGamma.Write();
    c2_electron_TTbar.Write();

   
    f->Close();
}
