void diplomka2(void)
{
    TFile* f = new TFile("antiNeu.root","READ");

    TH1F *hNInt = new TH1F("hNInt","Number of interactions for neutron;Number of interactions",80,0,80);
    TH1F *hNIntA = new TH1F("hNIntA","Number of interaction in the active volumes for neutron;Number of interaction",80,0,80);
    TH1F *hNIntP = new TH1F("hNIntP","Number of interaction in the pasive volumes for neutron;Number of interaction",80,0,80);

    TNtupleD* ntupleE = (TNtupleD*)f->Get("ntupleN");

    TCanvas* c = new TCanvas("c","Results",800,600);

    ntupleE->Draw("nInt >> hNInt");
    ntupleE->Draw("nIntA >> hNIntA");
    ntupleE->Draw("nIntP >> hNIntP");

    hNInt->SetLineColor(kRed);
    hNIntA->SetLineColor(kBlue);
    hNIntP->SetLineColor(kGreen);

    hNInt->Draw();
    hNIntA->Draw("same");
    hNIntP->Draw("same");

    hNInt->GetYaxis()->SetRangeUser(0,1000);

    TLegend *legend = new TLegend(0.45,0.78,0.95,0.4);
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->SetTextSize(0.05);
    legend->AddEntry(hNInt,"In all volumes", "l");
    legend->AddEntry(hNIntA,"In active volumes", "l");
    legend->AddEntry(hNIntP,"In pasive volumes", "l");

    legend->Draw();

    TH1F *hEne = new TH1F("hEne","Deposited energy of neutron;E [MeV]",100,0,0.01);
    TH1F *hEneA = new TH1F("hEneA","Deposited energy of neutron;E [MeV]",100,0,0.01);
    TH1F *hEneP = new TH1F("hEneP","Deposited energy of neutron;E [MeV]",100,0,0.01);

    TCanvas* c2 = new TCanvas("c2","Results",800,600);

    ntupleE->Draw("depEne >> hEne");
    ntupleE->Draw("depEneA >> hEneA");
    ntupleE->Draw("depEneP >> hEneP");

    hEne->SetLineColor(kRed);
    hEneA->SetLineColor(kBlue);
    hEneP->SetLineColor(kGreen);

    hEne->Draw();
    hEneA->Draw("same");
    hEneP->Draw("same");

    TLegend *legend = new TLegend(0.45,0.78,0.95,0.4);
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->SetTextSize(0.05);
    legend->AddEntry(hEne,"In all volumes", "l");
    legend->AddEntry(hEneA,"In active volumes", "l");
    legend->AddEntry(hEneP,"In pasive volumes", "l");

    legend->Draw();

    TH1F *hDist = new TH1F("hDist","Track length and distance from vertex for neutron;Length [mm]",1000,0,1000);
    TH1F *hTrackLen = new TH1F("hTrackLen","Track length and distance from vertex for neutron;Length [mm]",1000,0,1000);

    TCanvas* c3 = new TCanvas("c3","Results",800,600);

    ntupleE->Draw("dist >> hDist");
    ntupleE->Draw("trackLength >> hTrackLen");

    hDist->SetLineColor(kRed);
    hTrackLen->SetLineColor(kBlue);

    hDist->Draw();
    hTrackLen->Draw("same");

    TLegend *legend = new TLegend(0.45,0.78,0.95,0.4);
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->SetTextSize(0.05);
    legend->AddEntry(hDist,"Distance from vertex", "l");
    legend->AddEntry(hTrackLen,"Track length", "l");

    legend->Draw();

    TH1F *hMult = new TH1F("hMult","Multiplicity of hits for neutron;Number of hitted plates",20,0,20);

    TCanvas* c4 = new TCanvas("c4","Results",800,600);

    ntupleE->Draw("Multiplicity >> hMult");


}
