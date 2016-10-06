void final(void)
{
    double time;
    int number;

    TFile* rootFile = new TFile("results.root","READ");
    TTree* analyzedTree = (TTree*)rootFile->Get("eventTree");
    analyzedTree->SetBranchAddress("timeDist",&time);
    analyzedTree->SetBranchAddress("neutronCapturedGammaProduced",&number);


    TH1F *h1 = new TH1F("h1","Time distribution;t[#mus]",300,0,150);

    TH1F *h2 = new TH1F("h2","Number of gammas from neutron capture;Number of #gamma",12,0,12);

    //analyzedTree->Draw("timeDist >> h1");
    analyzedTree->Draw("neutronCapturedGammaProduced >> h2");

}
