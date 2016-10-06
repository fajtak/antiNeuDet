

void skript(void)
{
    TCanvas* c = new TCanvas("c","Results",800,600);
    c->Divide(1,2);
    TFile* f = new TFile("antiNeu.root","READ");

    //f->ls();
    TH1F *hTime = new TH1F("hTime","Time of neutron capture",400,0,200);
    TH1F *hTime2 = new TH1F("hTime2","Time of pozitron annihilation",200,0,200);

    TTree* tree = (TTree*)f->Get("hitTree;10");

    TCut cutLength = "(trackLength > 20)";
    TCut cutNeutron = "PDGencoding == 2112";
    TCut cutCapture = "stepProcess == \"nCapture\"";
    TCut cutKiller = "stepProcess == \"nKiller\"";
    TCut cutAnnih = "stepProcess == \"annihil\"";
    TCut cutTime = "globalTime > 1.5";
    TCut cutInit = "creationProcess == \"InitStep\"";
    TCut cutStepID = "stepID == 1";

    //TBranch *newBranch = tree->Branch("globalTime", &globalTime, "globalTime/F");
    c->cd(1);
    tree->Draw("globalTime >> +hTime",cutCapture);
    c->cd(2);
    tree->Draw("globalTime >> +hTime2",cutAnnih);



    /*TH2F *hPos = new TH2F("hpos","position",100,-50,50,100,-50,50);
    TH1F *hEneAll = new TH1F("hEneAll","EnergyAll",100,0,16);
    TH1F *hEneNeu = new TH1F("hEneNeu","EnergyNeutron",100,0,16);
    TH1F *hEneGam = new TH1F("hEneGam","EnergyGamma",100,0,16);
    TH1F *hEneEle = new TH1F("hEneEle","EnergyElectron",100,0,16);
    TH1F *hEnePro = new TH1F("hEnePro","EnergyProton",100,0,16);

    TCut cutEnergy = "(Energy < 15)";
    TCut cutNeutron = "(Name == 0)";
    TCut cutAll = "(Energy < 50)";
    TCut cutGamma = "(Name == 4)";
    TCut cutProton = "(Name == 1)";
    TCut cutElectron = "(Name == 2)";
    TCut cutPosition = "(valecek(posX,posY) < 5";

    TNtupleD* ntuple = (TNtupleD*)f->Get("ntuple;5");
    c->cd(1);
    ntuple->Draw("PosX:PosY >> +hpos",cutEnergy,"colz");
    c->cd(2);
    ntuple->Draw("Energy >> +hEneAll");
    c->cd(3);
    ntuple->Draw("Energy >> +hEneNeu",cutNeutron);
    c->cd(4);
    ntuple->Draw("Energy >> +hEneGam",cutGamma);
    c->cd(5);
    ntuple->Draw("Energy >> +hEneEle",cutElectron);
    c->cd(6);
    ntuple->Draw("Energy >> +hEnePro", cutProton);
    //ntuple->Draw("Energy >> +hEneGam", cutNeutron, "SAME");

    gROOT->LoadMacro("myclass.C");
    myclass *trida = new myclass(ntuple);

    int nInteract[10] = {0};

    ntuple->GetEntry(ntuple->GetEntries()-1);
    const int MaxEvent = (int)trida->EventID;
    int *pnArray = new int[MaxEvent]();
    int castice[7] = {0};

    int nNonInter = 0;

    for (int i = 0; i < MaxEvent; i++)
    {
        pnArray[i] = 0;
    }
    for (int i = 0; i < ntuple->GetEntries(); i++)
    {
        ntuple->GetEntry(i);
        pnArray[(int)trida->EventID]++;
        if (trida->Energy == 15 && trida->Name == 0) nNonInter++;
        castice[(int)trida->Name]++;
    }
    for (int i = 0; i < MaxEvent; i++)
    {
        //cout << i << " " << pnArray[i] << endl;
        nInteract[pnArray[i]]++;
    }

    cout << "Pocet detekcí : " << ntuple->GetEntries() << " Pocet udalosti : " << nInteract[0] << " " << nInteract[1] << " " << nInteract[2] << " " << nInteract[3] << " " << nInteract[4]<< " " << nInteract[5] << endl;
    cout << "Pocet pruchodu bez interakce : " << nNonInter << endl;
    cout << "Pocty castic : " << castice[0] << " neutronu " << castice[1] << " protonu " << castice[2] << " elektronu " << castice[3] << " pozitronu " << castice[4] << " gamma " << castice[5] << " anti_nu_e " << castice[6] << " ostatni" << endl;

    delete[] pnArray;*/
}
