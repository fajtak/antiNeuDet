void diplomka5(void)
{
    TFile* f = new TFile("results.root","READ");

    TTree* analyzedTree = (TTree*)f->Get("eventTree");

    TCanvas* c = new TCanvas("c","Results",800,600);

    TH1F *hTimeDist = new TH1F("hTimeDist",";t[#mus]",100,0,150);

    analyzedTree->Draw("timeDist >> hTimeDist");


    TCanvas* c1 = new TCanvas("c1","Results",800,600);

    TH1F *hPGFirstEne = new TH1F("hPGFirstEne",";E[MeV]",200,0,1);

    analyzedTree->Draw("pgFirstEnergies >> hPGFirstEne");

    TCanvas* c2 = new TCanvas("c2","Results",800,600);

    TH1F *hPGFirstDist= new TH1F("hPGFirstDist",";l[mm]",500,0,1000);

    analyzedTree->Draw("pgFirstDist >> hPGFirstDist");

    TCanvas* c3 = new TCanvas("c3","Results",800,600);

    TH1F *hNGSumDepEne= new TH1F("hNGSumDepEne",";E[MeV]",200,0,10);

    analyzedTree->Draw("neutronGammasSumDepEne >> hNGSumDepEne");
}
