#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include "event.h"
#include "TApplication.h"
#include "TString.h"
#include "TVector3.h"
#include "TROOT.h"
#include "TObjString.h"

#include "histo.h"

using namespace std;

struct interaction
{
    int runID;
    int eventID;
    int trackID;
    int stepID;
    int parentID;
    int PDGencoding;
    int replicaNScint;
    int replicaNStack;
    int layerID;

    char parNam[50];
    char crePro[50];
    char stePro[50];

    TVector3 position;
    TVector3 vertexPosition;

    bool activeVolume;
    bool outOfWorld;

    double globalTime;
    double trackLength;
    double kineticEnergy;
    double vertexKineticEnergy;
    double stepLength;
    double totalEnergyDeposition;
} ;

void AllocateEvents(Event* &Events, TTree* analyzedTree, int &nEvents)
{
    int nEntries = analyzedTree->GetEntries();
    int eventID = 0;
    analyzedTree->SetBranchAddress("eventID",&eventID);
    analyzedTree->GetEntry(nEntries-1);
    Events = new Event[eventID+1];
    nEvents = eventID+1;
}

void SetBranches(TTree* analyzedTree, interaction &intReader)
{
    analyzedTree->SetBranchAddress("runID",&intReader.runID);
    analyzedTree->SetBranchAddress("eventID",&intReader.eventID);
    analyzedTree->SetBranchAddress("trackID",&intReader.trackID);
    analyzedTree->SetBranchAddress("stepID",&intReader.stepID);
    analyzedTree->SetBranchAddress("parentID",&intReader.parentID);
    analyzedTree->SetBranchAddress("PDGencoding",&intReader.PDGencoding);
    analyzedTree->SetBranchAddress("replicaNScint",&intReader.replicaNScint);
    analyzedTree->SetBranchAddress("replicaNStack",&intReader.replicaNStack);
    analyzedTree->SetBranchAddress("layerID",&intReader.layerID);

    analyzedTree->SetBranchAddress("particleName",&intReader.parNam);
    analyzedTree->SetBranchAddress("creationProcess",&intReader.crePro);
    analyzedTree->SetBranchAddress("stepProcess",&intReader.stePro);

    analyzedTree->SetBranchAddress("positionX",&intReader.position[0]);
    analyzedTree->SetBranchAddress("positionY",&intReader.position[1]);
    analyzedTree->SetBranchAddress("positionZ",&intReader.position[2]);

    analyzedTree->SetBranchAddress("vertexPositionX",&intReader.vertexPosition[0]);
    analyzedTree->SetBranchAddress("vertexPositionY",&intReader.vertexPosition[1]);
    analyzedTree->SetBranchAddress("vertexPositionZ",&intReader.vertexPosition[2]);

    analyzedTree->SetBranchAddress("activeVolume",&intReader.activeVolume);
    analyzedTree->SetBranchAddress("outOfWorld",&intReader.outOfWorld);

    analyzedTree->SetBranchAddress("globalTime",&intReader.globalTime);
    analyzedTree->SetBranchAddress("trackLength",&intReader.trackLength);
    analyzedTree->SetBranchAddress("kineticEnergy",&intReader.kineticEnergy);
    analyzedTree->SetBranchAddress("vertexKineticEnergy",&intReader.vertexKineticEnergy);
    analyzedTree->SetBranchAddress("stepLength",&intReader.stepLength);
    analyzedTree->SetBranchAddress("TotalEnergyDeposition",&intReader.totalEnergyDeposition);
}

void ReadData(Event* &allEvents, int &nEvents)
{
    //TFile* rootFile = new TFile("../test.root","READ");
    TFile* rootFile = new TFile("../antiNeu.root","READ");
    TTree* analyzedTree = (TTree*)rootFile->Get("hitTree");
    //TTree* analyzedTree = (TTree*)rootFile->Get("hitTree;120");
    AllocateEvents(allEvents,analyzedTree,nEvents);
    interaction intReader;
    SetBranches(analyzedTree,intReader);
    int nEntries = analyzedTree->GetEntries();
    int idTracks = 0;
    int nReadEvents = 0;
    int nReadTracks = 0;
    for (int i = 0 ; i < nEntries ; i++)
    {
        analyzedTree->GetEntry(i);
        if (intReader.runID > 0)
        {
            cout << "Vicero runu, musi se doprogramovat!";
            break;
        }
        if (intReader.eventID != nReadEvents)
        {
            nReadEvents++;
            idTracks = 0;
            nReadTracks = 0;
        }
        if (intReader.trackID != idTracks)
        {
            allEvents[intReader.eventID].AddTrack(intReader.trackID,intReader.parentID,intReader.PDGencoding,intReader.parNam,intReader.crePro,intReader.vertexPosition,intReader.trackLength,intReader.vertexKineticEnergy,intReader.outOfWorld);
            idTracks = intReader.trackID;
            nReadTracks++;
        }
        allEvents[intReader.eventID].GetTrack(nReadTracks-1)->AddVertex(intReader.stepID,intReader.replicaNScint,intReader.replicaNStack,intReader.layerID,intReader.stePro,intReader.position,intReader.activeVolume,intReader.globalTime,intReader.kineticEnergy,intReader.stepLength,intReader.totalEnergyDeposition);
        allEvents[intReader.eventID].GetTrack(nReadTracks-1)->Update(intReader.trackLength,intReader.outOfWorld);
    }
    TObjString* dim = (TObjString*)(analyzedTree->GetUserInfo()->At(1));
    rootFile->Close();
}

void ProcessEvents(Event* allEvents, int nEvents)
{
    for (int i = 0 ; i < nEvents ; i++)
    {
        //allEvents[i].PrintTracks();
        allEvents[i].ProcessNeutrons();
        allEvents[i].ProcessPozitrons();
        allEvents[i].ProcessRest();
    }
}

void SaveEvents(Event* allEvents, int nEvents)
{
    Histo* histograms = Histo::GetInstance();
    for (int i = 0 ; i < nEvents ; i++)
    {
        //if (i == 0)
            //histograms->SavePathPic(allEvents[i]);
        histograms->UpdateEvent(allEvents[i]);
    }
    histograms->SaveEnergies(allEvents, nEvents);
}

int main(int argc, char* argv[])
{
    gROOT->SetBatch(kTRUE);
    TApplication* theApp = new TApplication("App", &argc, argv);
    //argc = theApp->Argc();
    //argv = theApp->Argv();

    int nEvents = 0;
    Event* allEvents = NULL;

    ReadData(allEvents,nEvents);

    Histo* histograms = Histo::GetInstance();
    histograms->AMSetup();

    cout << "Start processing!" << endl;

    ProcessEvents(allEvents,nEvents);
    SaveEvents(allEvents,nEvents);

    histograms->AMDelete();
    //theApp->Run();
    delete[] allEvents;

    return 0;
}
