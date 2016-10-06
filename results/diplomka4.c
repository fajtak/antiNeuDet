void diplomka4(void)
{
    TFile* f = new TFile("results.root","READ");

    TH1F *hPAnnihil = new TH1F("hPAnnihil",";Annihilated [0 = NO, 1 = YES]",2,0,2);
    TH1F *hPGammasEnergies = new TH1F("hPGammasEnergies",";Energy [MeV]",120,0,6);
    TH1F *hPInitialEnergy = new TH1F("hPInitialEnergy",";Energy [MeV]",100,0,10);

    TTree* analyzedTree = (TTree*)f->Get("eventTree");

    TCanvas* c = new TCanvas("c","Results",800,600);

    analyzedTree->Draw("pozitronAnnihil >> hPAnnihil");

    TCanvas* c1 = new TCanvas("c1","Results",800,600);

    analyzedTree->Draw("pozitronGammasEnergies >> hPGammasEnergies");
    hPGammasEnergies->DrawClone();

    TCanvas* c2 = new TCanvas("c2","Results",800,600);

    hPGammasEnergies->GetYaxis()->SetRangeUser(0,100);
    hPGammasEnergies->DrawClone();

    TCanvas* c3 = new TCanvas("c3","Results",800,600);

    analyzedTree->Draw("pozitronInitialEnergy >> hPInitialEnergy");
}
