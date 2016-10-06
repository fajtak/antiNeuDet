#include "histo.h"

Histo::Histo()
{
}

Histo::~Histo()
{

}

Histo* Histo::instance = 0;

Histo* Histo::GetInstance()
{
    if (instance == 0) instance = new Histo;
    return instance;
}

void Histo::AMSetup(){

    fileROOT=0;

    char name[50];

    // Open an output ROOT file
    strcpy(name, "results");
    strcat(name,".root");
    fileROOT = new TFile(name,"UPDATE");

    if (fileROOT == NULL) {
        cout << "Unable to open " <<  name << " !!!" << endl;
        exit(1);
    }
    cout << "Output file " <<  name << " opened..." << endl;
    BookTree();
}

void Histo::AMDelete(){

    eventTree -> Write();

    // Close ROOT file
    fileROOT->Close();
    delete fileROOT;
    fileROOT = 0;

    cout << "Output file properly closed..." << endl;
}

void Histo::BookTree()
{
    eventTree = new TTree("eventTree","Events");
    eventTree->Branch("neutronCaptured",&currentEvent.neutronCaptured,"neutronCaptured/O");
    eventTree->Branch("neutronEscaped",&currentEvent.neutronEscaped,"neutronEscaped/O");
    eventTree->Branch("neutronCapturedGammaProduced",&currentEvent.neutronCapturedGammaProduced,"neutronCapturedGammaProduced/I");
    eventTree->Branch("neutronGammasEnergies",&currentEvent.neutronGammasEnergies);
    eventTree->Branch("neutronGammasEnergiesSum",&currentEvent.neutronGammasEnergiesSum,"neutronGammaEnergiesSum/D");
    eventTree->Branch("neutronNIntBeforeCapture",&currentEvent.neutronNIntBeforeCapture,"neutronNIntBeforeCapture/I");
    eventTree->Branch("neutronTrackLength",&currentEvent.neutronTrackLength,"neutronTrackLength/D");
    eventTree->Branch("neutronDistance",&currentEvent.neutronDistance,"neutronDistance/D");
    eventTree->Branch("neutronGdCaptured",&currentEvent.neutronGdCaptured,"neutronGdCaptured/O");
    eventTree->Branch("neutronInitialEnergy",&currentEvent.neutronInitialEnergy,"neutronInitialEnergy/D");
    eventTree->Branch("neutronMultiplicity",&currentEvent.neutronMultiplicity,"neutronMultiplicity/I");

    eventTree->Branch("pozitronAnnihil",&currentEvent.pozitronAnnihil,"pozitronAnnihil/O");
    eventTree->Branch("pozitronEscaped",&currentEvent.pozitronEscaped,"pozitronEscaped/O");
    eventTree->Branch("pozitronAnnihilGammaProduced",&currentEvent.pozitronAnnihilGammaProduced,"pozitronAnnihilGammaProduced/I");
    eventTree->Branch("pozitronGammasEnergies",&currentEvent.pozitronGammasEnergies);
    eventTree->Branch("pozitronNIntBeforeAnnihil",&currentEvent.pozitronNIntBeforeAnnihil,"pozitronNIntBeforeAnnihil/I");
    eventTree->Branch("pozitronTrackLength",&currentEvent.pozitronTrackLength,"pozitronTrackLength/D");
    eventTree->Branch("pozitronDistance",&currentEvent.pozitronDistance,"pozitronDistance/D");
    eventTree->Branch("pozitronInitialEnergy",&currentEvent.pozitronInitialEnergy,"pozitronInitialEnergy/D");
    eventTree->Branch("pozitronMultiplicity",&currentEvent.pozitronMultiplicity,"pozitronMultiplicity/I");

    eventTree->Branch("timeDist",&currentEvent.timeDist,"timeDist/D");
    eventTree->Branch("pgFirstEnergies",currentEvent.pgFirstEnergies,"pgFirstEnergies[2]/D");
    eventTree->Branch("pgBothDetected",&currentEvent.pgBothDetected,"pgBothDetected/O");
    eventTree->Branch("pgOneDetected",&currentEvent.pgOneDetected,"pgOneDetected/O");
    eventTree->Branch("pgFirstDist",currentEvent.pgFirstDist,"pgFirstDist[2]/D");
    eventTree->Branch("neutronGammasSumDepEne",&currentEvent.neutronGammasSumDepEne,"neutronGammasSumDepEne/D");
}

void Histo::UpdateEvent(Event &newEvent)
{
    currentEvent.neutronCaptured = newEvent.GetNeutronCaptured();
    currentEvent.neutronEscaped = newEvent.GetNeutronEscaped();
    currentEvent.neutronCapturedGammaProduced = newEvent.GetNeutronCapturedGammaProduced();
    currentEvent.neutronGammasEnergies = newEvent.GetNeutronGammaEnergies();
    currentEvent.neutronGammasEnergiesSum = newEvent.GetNeutronGammaEnergiesSum();
    currentEvent.neutronNIntBeforeCapture = newEvent.GetNeutronNIntBeforeCapture();
    currentEvent.neutronTrackLength = newEvent.GetNeutronTrackLength();
    currentEvent.neutronDistance = newEvent.GetNeutronDistance();
    currentEvent.neutronGdCaptured = newEvent.GetNeutronGdCaptured();
    currentEvent.neutronInitialEnergy = newEvent.GetNeutronInitialEnergy();
    currentEvent.neutronMultiplicity = newEvent.GetNeutronMultiplicity();

    currentEvent.pozitronAnnihil = newEvent.GetPozitronAnnihil();
    currentEvent.pozitronEscaped = newEvent.GetPozitronEscaped();
    currentEvent.pozitronAnnihilGammaProduced = newEvent.GetPozitronAnnihilGammaProduced();
    currentEvent.pozitronGammasEnergies = newEvent.GetPozitronGammaEnergies();
    currentEvent.pozitronNIntBeforeAnnihil = newEvent.GetPozitronNIntBeforeAnnihil();
    currentEvent.pozitronTrackLength = newEvent.GetPozitronTrackLength();
    currentEvent.pozitronDistance = newEvent.GetPozitronDistance();
    currentEvent.pozitronInitialEnergy = newEvent.GetPozitronInitialEnergy();
    currentEvent.pozitronMultiplicity = newEvent.GetPozitronMultiplicity();

    currentEvent.timeDist = newEvent.GetTimeDist();
    currentEvent.pgFirstEnergies[0] = newEvent.GetPGFirstEnergies(0);
    currentEvent.pgFirstEnergies[1] = newEvent.GetPGFirstEnergies(1);

    currentEvent.pgBothDetected = ((currentEvent.pgFirstEnergies[0] > 0.035)&&(currentEvent.pgFirstEnergies[1] > 0.035));
    currentEvent.pgOneDetected = ((currentEvent.pgFirstEnergies[0] > 0.035)||(currentEvent.pgFirstEnergies[1] > 0.035));

    currentEvent.pgFirstDist[0] = newEvent.GetPGFirstDist(0);
    currentEvent.pgFirstDist[1] = newEvent.GetPGFirstDist(1);

    currentEvent.neutronGammasSumDepEne = newEvent.GetNeutronGammasSumDepEne();

    eventTree->Fill();
}

void Histo::SavePathPic(Event &processEvent)
{
    TCanvas* myCan = new TCanvas("myCan","Neutron path",1024,768);
    myCan->Divide(2,2);
    Track* neutronTrack = processEvent.FindPrimaryTrackParticleName("neutron");
    int nVertices = neutronTrack->GetNVertices();

    TGraph* XYpathGraph = new TGraph(nVertices);
    TGraph* XZpathGraph = new TGraph(nVertices);
    TGraph* YZpathGraph = new TGraph(nVertices);
    TGraph2D* path3D = new TGraph2D(nVertices);

    XYpathGraph->SetLineColor(kGreen);
    XYpathGraph->SetLineWidth(2);


    XZpathGraph->SetLineColor(kGreen);
    XZpathGraph->SetLineWidth(2);
    YZpathGraph->SetLineColor(kGreen);
    YZpathGraph->SetLineWidth(2);

    path3D->SetLineColor(kGreen);
    path3D->SetLineWidth(2);
    path3D->SetMarkerColor(kBlue);
    path3D->SetMarkerStyle(2);

    for (int i = 0 ; i < nVertices+1 ; i++)
    {
        if (i == 0 )
        {
            XYpathGraph->SetPoint(i,neutronTrack->GetVertexPositionX(),neutronTrack->GetVertexPositionY());
            XZpathGraph->SetPoint(i,neutronTrack->GetVertexPositionX(),neutronTrack->GetVertexPositionZ());
            YZpathGraph->SetPoint(i,neutronTrack->GetVertexPositionY(),neutronTrack->GetVertexPositionZ());
            path3D->SetPoint(i,neutronTrack->GetVertexPositionX(),neutronTrack->GetVertexPositionY(),neutronTrack->GetVertexPositionZ());
        }else{
            XYpathGraph->SetPoint(i,neutronTrack->GetVertex(i-1)->GetPositionX(),neutronTrack->GetVertex(i-1)->GetPositionY());
            XZpathGraph->SetPoint(i,neutronTrack->GetVertex(i-1)->GetPositionX(),neutronTrack->GetVertex(i-1)->GetPositionZ());
            YZpathGraph->SetPoint(i,neutronTrack->GetVertex(i-1)->GetPositionY(),neutronTrack->GetVertex(i-1)->GetPositionZ());
            path3D->SetPoint(i,neutronTrack->GetVertex(i-1)->GetPositionX(),neutronTrack->GetVertex(i-1)->GetPositionY(),neutronTrack->GetVertex(i-1)->GetPositionZ());
        }
    }
    myCan->cd(1);
    XYpathGraph->Draw("AL");
    TLine* b = new TLine();
    b->SetLineColor(kRed);
    b->DrawLine(-200,-200,-200,200);
    b->DrawLine(0,-200,0,200);
    b->DrawLine(200,-200,200,200);
    b->DrawLine(-200,-200,200,-200);
    b->DrawLine(-200,0,200,0);
    b->DrawLine(-200,200,200,200);

    myCan->cd(2);
    XZpathGraph->Draw("AL");
    myCan->cd(3);
    YZpathGraph->Draw("AL");
    myCan->cd(4);
    path3D->Draw("PLINE");

    XYpathGraph->GetXaxis()->SetLimits(-300,300);
    XYpathGraph->GetHistogram()->SetMaximum(300);
    XYpathGraph->GetHistogram()->SetMinimum(-300);
    XZpathGraph->GetXaxis()->SetLimits(-300,300);
    XZpathGraph->GetHistogram()->SetMaximum(300);
    XZpathGraph->GetHistogram()->SetMinimum(-300);
    YZpathGraph->GetXaxis()->SetLimits(-300,300);
    YZpathGraph->GetHistogram()->SetMaximum(300);
    YZpathGraph->GetHistogram()->SetMinimum(-300);

    myCan->Update();

    myCan->Write();
}

void Histo::SaveEnergies(Event* allEvents, int nEvents)
{
    //TGraph* XYpathGraph = new TGraph(nVertices);
    //TGraph* XZpathGraph = new TGraph(nVertices);
    //TGraph* YZpathGraph = new TGraph(nVertices);
    TH1F* delayZer = new TH1F("delayZer","Delay signal from channel 0",40,0,10);
    TH1F* delayOne = new TH1F("delayOne","Delay signal from channel 1",40,0,10);
    TH1F* delaySum = new TH1F("delaySum","Delay signal from both channels",40,0,10);
    TH1F* promptZer = new TH1F("promptZer","Prompt signal from channel 0",40,0,10);
    TH1F* promptOne = new TH1F("promptOne","Prompt signal from channel 1",40,0,10);
    TH1F* promptSum = new TH1F("promptSum","Prompt signal from both channels",40,0,10);
    TGraph* pozitronScatt = new TGraph(nEvents);

    pozitronScatt->SetMarkerColor(kBlue);
    pozitronScatt->SetMarkerStyle(2);

    int nDetectedOr = 0;
    int nDetectedAnd = 0;

    for (int i = 0 ; i < nEvents ; i++)
    {
        delayZer->Fill(allEvents[i].GetDelayEne(0));
        delayOne->Fill(allEvents[i].GetDelayEne(1));
        delaySum->Fill(allEvents[i].GetDelayEne(0)+allEvents[i].GetDelayEne(1));
        promptZer->Fill(allEvents[i].GetPromptEne(0));
        promptOne->Fill(allEvents[i].GetPromptEne(1));
        promptSum->Fill(allEvents[i].GetPromptEne(0)+allEvents[i].GetPromptEne(1));
        pozitronScatt->SetPoint(i,allEvents[i].GetPozitronInitialEnergy(),allEvents[i].GetPromptEne(0)+allEvents[i].GetPromptEne(1));

        //if (((allEvents[i].GetPromptEne(0) > 0.25)&&(allEvents[i].GetDelayEne(0) > 1))||((allEvents[i].GetPromptEne(1) > 0.25)&&(allEvents[i].GetDelayEne(1) > 1)))
        double Ethr = 1.5;
        if (((allEvents[i].GetPromptEne(0) > Ethr)||(allEvents[i].GetPromptEne(1) > Ethr))&&((allEvents[i].GetDelayEne(0) > Ethr)||(allEvents[i].GetDelayEne(1) > Ethr))&&allEvents[i].GetTimeDist()>1)
            nDetectedOr++;
        if (((allEvents[i].GetPromptEne(0) > Ethr)||(allEvents[i].GetPromptEne(1) > Ethr))&&((allEvents[i].GetDelayEne(0) > Ethr)&&(allEvents[i].GetDelayEne(1) > Ethr))&&allEvents[i].GetTimeDist()>1)
            nDetectedAnd++;
    }

    cout << "Efficiency of your detecter is (OR) : " << (double)nDetectedOr/nEvents*100 << " %" << endl;
    cout << "Efficiency of your detecter is (AND) : " << (double)nDetectedAnd/nEvents*100 << " %" << endl;

    delayZer->Write();
    delayOne->Write();
    delaySum->Write();
    promptZer->Write();
    promptOne->Write();
    promptSum->Write();
    pozitronScatt->Write();
}

/*void Histo::BookNtuple()
{
    ntupleE = new TNtupleD("ntupleE","positron","nInt");
    ntupleN = new TNtupleD("ntupleN","neutron","nInt");
}

void Histo::FillNtupleE()
{
    double i = 0;
    //ntupleE->Fill(i);
}

void Histo::FillNtupleN()
{
    double i = 0;
    //ntupleN->Fill();
}

void Histo::FillTree()
{
    hitTree->Fill();
}


void Histo::SaveNtuple()
{
    ntupleE -> Write();
    ntupleN -> Write();
    hitTree -> Write();
}

void Histo::HitInit()
{
    ;
}

void Histo::HitProcess()
{
    FillTree();

}

void Histo::HitFinish()
{
    ;
}*/
