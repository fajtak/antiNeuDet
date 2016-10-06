#ifndef HISTO_H
#define HISTO_H

#include <iostream>

#include "TFile.h"
#include "TNtupleD.h"
#include "TTree.h"
#include "TH1F.h"
#include "TList.h"
#include "TObjString.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TGraph2D.h"
#include "TBox.h"
#include "TLine.h"

#include "event.h"
#include "track.h"
#include "vertex.h"

using namespace std;

struct eventStruct
{
    bool neutronCaptured;
    bool neutronEscaped;
    int neutronCapturedGammaProduced;
    vector<double> neutronGammasEnergies;
    double neutronGammasEnergiesSum;
    int neutronNIntBeforeCapture;
    double neutronTrackLength;
    double neutronDistance;
    bool neutronGdCaptured;
    double neutronInitialEnergy;
    int neutronMultiplicity;

    bool pozitronAnnihil;
    bool pozitronEscaped;
    int pozitronAnnihilGammaProduced;
    vector<double> pozitronGammasEnergies;
    int pozitronNIntBeforeAnnihil;
    double pozitronTrackLength;
    double pozitronDistance;
    double pozitronInitialEnergy;
    int pozitronMultiplicity;

    double timeDist;
    double pgFirstEnergies[2];
    double pgFirstDist[2];
    bool pgBothDetected;
    bool pgOneDetected;

    double neutronGammasSumDepEne;
};

class Histo
{
public:

    ~Histo();

    static Histo *GetInstance();

    void BookTree();
    void UpdateEvent(Event &newEvent);
    void SavePathPic(Event &processEvent);
    void SaveEnergies(Event* allEvents, int nEvents);
    //void BookNtuple();
    //void FillNtupleE();
    //void FillNtupleN();
    //void FillTree();
    //void SaveNtuple();

    //void HitInit();
    //void HitProcess();
    //void HitFinish();
    void AMSetup();
    void AMDelete();

private:

    Histo();

    static Histo* instance;

    char rootFileName[50];
    TFile* fileROOT;

    TTree*    eventTree;
    eventStruct currentEvent;


};

#endif // HISTO_H
