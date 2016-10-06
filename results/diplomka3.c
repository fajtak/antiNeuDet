void diplomka3(void)
{
    TFile* f = new TFile("results.root","READ");

    TH1F *hNCaptured = new TH1F("hNCaptured",";Captured [0 = NO, 1 = YES]",2,0,2);
    TH1F *hNGdCaptured = new TH1F("hNGdCaptured",";Captured on Gd [0 = NO, 1 = YES]",2,0,2);
    TH1F *hNCapturedGammaProduced = new TH1F("hNCapturedGammaProduced",";Number of gammas",15,0,15);
    TH1F *hNGammasEnergiesSum = new TH1F("hNGammasEnergiesSum",";Energy [MeV]",1500,0,15);
    TH1F *hNInitialEnergy = new TH1F("hNInitialEnergy",";Energy [MeV]",100,0,0.1);
    TH1F *hNGammasEnergies = new TH1F("hNGammasEnergies",";Energy [MeV]",1500,0,15);

    TTree* analyzedTree = (TTree*)f->Get("eventTree");

    TCanvas* c = new TCanvas("c","Results",800,600);

    analyzedTree->Draw("neutronCaptured >> hNCaptured");

    TCanvas* c1 = new TCanvas("c1","Results",800,600);

    analyzedTree->Draw("neutronGdCaptured >> hNGdCaptured");

    TCanvas* c2 = new TCanvas("c2","Results",800,600);

    analyzedTree->Draw("neutronCapturedGammaProduced >> hNCapturedGammaProduced");

    TCanvas* c3 = new TCanvas("c3","Results",800,600);

    analyzedTree->Draw("neutronGammasEnergiesSum >> hNGammasEnergiesSum");

    TCanvas* c4 = new TCanvas("c4","Results",800,600);

    analyzedTree->Draw("neutronInitialEnergy >> hNInitialEnergy");

    TCanvas* c5 = new TCanvas("c5","Results",800,600);

    analyzedTree->Draw("neutronGammasEnergies >> hNGammasEnergies");
}
