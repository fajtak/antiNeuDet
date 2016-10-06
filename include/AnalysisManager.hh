#ifndef ANALYSISMANAGER_HH
#define ANALYSISMANAGER_HH

#include "G4ThreeVector.hh"
#include "globals.hh"

#include "TFile.h"
#include "TNtupleD.h"
#include "TTree.h"
#include "TH1F.h"
#include "TList.h"
#include "TObjString.h"

#include "ExN01TrackerHit.hh"

const int constMulti = 1000;

struct Info
{
    G4double  Distance;
    G4double  TrackLength;
    G4double  nIntA;
    G4double  DepEnergyA;
    G4double  nIntP;
    G4double  DepEnergyP;
    G4double  nInt;
    G4double  DepEnergy;
    G4double  depEneRatio;
    G4int     Multiplicity[constMulti];
    G4int     nMultiplicity;
};

/*class UserInfo : public TObject
{
    public:
        //UserInfo();
        void SetNameO(TString newValue){name = newValue;};
        void SetUnit(TString newValue){unit = newValue;};
        void SetValue(int newValue){valueI = newValue;};
        void SetValue(double newValue){valueD = newValue;};
        TString GetNameO(void){return name;};
        TString GetUnit(void){return unit;};
        int GetValueI(void){return valueI;};
        double GetValueD(void){return valueD;};

    private:
        TString name;
        TString unit;
        double valueD;
        int valueI;
};*/

class ExN01TrackerHit;

class AnalysisManager
{
public:

    ~AnalysisManager();

    static AnalysisManager *GetInstance();

    void BookNtuple();
    void FillNtupleE();
    void FillNtupleN();
    void FillTree();
    void SaveNtuple();

    void HitInit();
    void HitProcess(ExN01TrackerHit hitInfo);
    void HitFinish();
    void AMSetup();
    void AMDelete();

    void SetRunID(G4int newValue){runID = newValue;};
    void SetEventID(G4int newValue){eveID = newValue;};

    void UpdateScintDim(double x, double y, double z);
    void UpdateNumScint(int a, int b, int c);
    void UpdateDeadLayThic(double x);
    void UpdateGunInfo(int a, int b, int c, int d);
    void SaveRunInfo();

private:

    AnalysisManager();

    static AnalysisManager * instance;

    char rootFileName[50];
    TFile * fileROOT;

    TNtupleD* ntupleE;
    TNtupleD* ntupleN;
    TTree*    hitTree;

    Info          positron;
    Info          neutron;

    G4int         runID;
    G4int         eveID;
    G4int         traID;
    G4int         parID;
    G4int         steID;
    G4int         PDGenc;
    G4int         repNSci;
    G4int         repNSta;
    G4int         layID;

    char          parNam[50];
    char          crePro[50];
    char          stePro[50];

    G4double      posX;
    G4double      posY;
    G4double      posZ;
    G4double      verPosX;
    G4double      verPosY;
    G4double      verPosZ;

    G4double      gloTim;
    G4double      traLen;
    G4double      kinEne;
    G4double      verKinEne;
    G4double      steLen;
    G4double      totEneDep;

    G4bool        actVol;
    G4bool        outOfWorld;

    TObjString*   dimensions;
    TObjString*   numberOfScint;
    TObjString*   deadLayerThic;
    TObjString*   gunInfo;
};

#endif // ANALYSISMANAGER_HH
