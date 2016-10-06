#include "AnalysisManager.hh"

#include "globals.hh"

//
// Private constructor
//
AnalysisManager::AnalysisManager()
{
    dimensions = new TObjString();
    numberOfScint = new TObjString();
    deadLayerThic = new TObjString();
    gunInfo = new TObjString();
}

//
// Destructor
//
AnalysisManager::~AnalysisManager()
{
    delete dimensions;
    delete numberOfScint;
    delete deadLayerThic;
    delete gunInfo;
}

//
// Static instance of this class
//
AnalysisManager * AnalysisManager::instance = 0;

//
// Method constructing static instance of this class
//
AnalysisManager * AnalysisManager::GetInstance()
{
    if (instance == 0) instance = new AnalysisManager;
    return instance;
}

void AnalysisManager::AMSetup(){

    fileROOT=0;
    ntupleE=0;
    ntupleN=0;
    hitTree=0;

    char name[50];

    // Open an output ROOT file
    strcpy(name, "antiNeu");
    strcat(name,".root");
    fileROOT = new TFile(name,"ReCreate");

    if (fileROOT == NULL) {
        G4cout << "Unable to open " <<  name << " !!!" << G4endl;
        exit(1);
    }
    G4cout << "Output file " <<  name << " opened..." << G4endl;
    G4cout << "" << G4endl;

    // Allocate variables

}

void AnalysisManager::AMDelete(){

    // Delete ROOT ntuple
    delete ntupleE;
    delete ntupleN;
    delete hitTree;
    ntupleE = 0;
    ntupleN = 0;
    hitTree = 0;

    // Close ROOT file
    fileROOT -> Close();
    delete fileROOT;
    fileROOT = 0;

    G4cout << "Output file properly closed..." << G4endl;
    G4cout << "" << G4endl;
}

//
// Create an ntuple
//
void AnalysisManager::BookNtuple()
{
    // Book an ntuple
    ntupleE = new TNtupleD("ntupleE","positron","nInt:nIntA:nIntP:depEne:depEneA:depEneP:depEneRatio:dist:trackLength:Multiplicity");
    ntupleN = new TNtupleD("ntupleN","neutron","nInt:nIntA:nIntP:depEne:depEneA:depEneP:depEneRatio:dist:trackLength:Multiplicity");


    hitTree = new TTree("hitTree","Hits list");
    hitTree->Branch("runID",&runID);
    hitTree->Branch("eventID",&eveID);
    hitTree->Branch("trackID",&traID);
    hitTree->Branch("parentID",&parID);
    hitTree->Branch("stepID",&steID);
    hitTree->Branch("PDGencoding",&PDGenc);
    hitTree->Branch("replicaNScint",&repNSci);
    hitTree->Branch("replicaNStack",&repNSta);
    hitTree->Branch("layerID",&layID);

    hitTree->Branch("particleName",&parNam,"parNam/C");
    hitTree->Branch("creationProcess",&crePro,"crePro/C");
    hitTree->Branch("stepProcess",&stePro,"stePro/C");

    hitTree->Branch("positionX",&posX);
    hitTree->Branch("positionY",&posY);
    hitTree->Branch("positionZ",&posZ);
    hitTree->Branch("vertexPositionX",&verPosX);
    hitTree->Branch("vertexPositionY",&verPosY);
    hitTree->Branch("vertexPositionZ",&verPosZ);

    hitTree->Branch("activeVolume",&actVol);
    hitTree->Branch("outOfWorld",&outOfWorld);

    hitTree->Branch("globalTime",&gloTim);
    hitTree->Branch("trackLength",&traLen);
    hitTree->Branch("kineticEnergy",&kinEne);
    hitTree->Branch("vertexKineticEnergy",&verKinEne);
    hitTree->Branch("stepLength",&steLen);
    hitTree->Branch("TotalEnergyDeposition",&totEneDep);

    /*G4ThreeVector pos;
    G4ThreeVector verPos;*/
}

//
// Fill an ntuple
//
void AnalysisManager::FillNtupleE()
{
    ntupleE->Fill(positron.nInt,positron.nIntA,positron.nIntP,positron.DepEnergy,positron.DepEnergyA,positron.DepEnergyP,positron.depEneRatio,positron.Distance,positron.TrackLength,positron.nMultiplicity);
}
void AnalysisManager::FillNtupleN()
{
    ntupleN->Fill(neutron.nInt,neutron.nIntA,neutron.nIntP,neutron.DepEnergy,neutron.DepEnergyA,neutron.DepEnergyP,neutron.depEneRatio,neutron.Distance,neutron.TrackLength,neutron.nMultiplicity);
}
//
// Fill an tree
void AnalysisManager::FillTree()
{
    hitTree->Fill();
}

//
// Write the data to a file
//
void AnalysisManager::SaveNtuple()
{
    // Write the ntuple to a file ...
    //fileROOT -> cd();
    ntupleE -> Write();
    ntupleN -> Write();
    hitTree -> Write();
}
//
// Methods digitizing simulated data
//
//  Initialize
//
void AnalysisManager::HitInit()
{
    positron.Distance = neutron.Distance = 0;
    positron.TrackLength = neutron.TrackLength = 0;
    positron.nInt = neutron.nInt = 0;
    positron.nIntA = neutron.nIntA = 0;
    positron.nIntP = neutron.nIntP = 0;
    positron.DepEnergy = neutron.DepEnergy = 0;
    positron.DepEnergyA = neutron.DepEnergyA = 0;
    positron.DepEnergyP = neutron.DepEnergyP = 0;
    positron.depEneRatio = neutron.depEneRatio = 0;
    for (int i = 0; i < constMulti ; i++){
        positron.Multiplicity[i] = 0;
        neutron.Multiplicity[i] = 0;
    }
    positron.nMultiplicity = neutron.nMultiplicity = 0;
}

//
//  Process
//
void AnalysisManager::HitProcess(ExN01TrackerHit hitInfo)
{
    hitInfo.SetRunID(runID);
    hitInfo.SetEveID(eveID);

    if ((hitInfo.GetPDGenc() == -11)&&(hitInfo.GetParID() == 0)&&(hitInfo.GetStePro() != "Transportation")){
        if (hitInfo.GetActVol()){
            positron.DepEnergyA+= hitInfo.GetTotEneDep()/MeV;
            positron.nIntA++;
            int detID = hitInfo.GetRepNSta()*1000000+hitInfo.GetRepNSci()*10+hitInfo.GetLayID();
            bool newDetector = true;
            for (int j = 0; j <= positron.nMultiplicity ; j++){
                if (detID == positron.Multiplicity[j]) newDetector = false;
            }
            if (newDetector){
                positron.Multiplicity[positron.nMultiplicity] = detID;
                positron.nMultiplicity++;
            }
            //G4cout << detID << " " << nMultiplicity << G4endl;
            //G4cout << "A" << G4endl;
        }else{
            positron.DepEnergyP+= hitInfo.GetTotEneDep()/MeV;
            positron.nIntP++;
            //G4cout << "B" << G4endl;
        }
        positron.DepEnergy+= hitInfo.GetTotEneDep()/MeV;
        positron.nInt++;
        positron.Distance = hitInfo.GetDis()/mm;
        positron.TrackLength = hitInfo.GetTraLen()/mm;
        if (positron.DepEnergyA != 0)
            positron.depEneRatio = positron.DepEnergyP/positron.DepEnergyA;

    }
    if ((hitInfo.GetPDGenc() == 2112)&&(hitInfo.GetParID() == 0)&&(hitInfo.GetStePro() != "Transportation")){
        if (hitInfo.GetActVol()){
            neutron.DepEnergyA+= hitInfo.GetTotEneDep()/MeV;
            neutron.nIntA++;
            int detID = hitInfo.GetRepNSta()*1000000+hitInfo.GetRepNSci()*10+hitInfo.GetLayID();
            bool newDetector = true;
            for (int j = 0; j <= neutron.nMultiplicity ; j++){
                if (detID == neutron.Multiplicity[j]) newDetector = false;
            }
            if (newDetector){
                neutron.Multiplicity[neutron.nMultiplicity] = detID;
                neutron.nMultiplicity++;
            }
            //G4cout << detID << " " << nMultiplicity << G4endl;
            //G4cout << "A" << G4endl;
        }else{
            neutron.DepEnergyP+= hitInfo.GetTotEneDep()/MeV;
            neutron.nIntP++;
            //G4cout << "B" << G4endl;
        }
        neutron.DepEnergy+= hitInfo.GetTotEneDep()/MeV;
        neutron.nInt++;
        neutron.Distance = hitInfo.GetDis()/mm;
        neutron.TrackLength = hitInfo.GetTraLen()/mm;
        if (neutron.DepEnergyA != 0)
            neutron.depEneRatio = neutron.DepEnergyP/neutron.DepEnergyA;

    }
    //mhitInfo = hitInfo;
    traID = hitInfo.GetTraID();
    parID = hitInfo.GetParID();
    steID = hitInfo.GetSteID();
    PDGenc = hitInfo.GetPDGenc();
    repNSci = hitInfo.GetRepNSci();
    repNSta = hitInfo.GetRepNSta();
    layID = hitInfo.GetLayID();

    strcpy(parNam,hitInfo.GetParNam().Data());
    strcpy(crePro,hitInfo.GetCrePro().Data());
    strcpy(stePro,hitInfo.GetStePro().Data());

    gloTim = hitInfo.GetGloTim();
    traLen = hitInfo.GetTraLen();
    kinEne = hitInfo.GetKinEne();
    verKinEne = hitInfo.GetVerKinEne();
    steLen = hitInfo.GetSteLen();
    totEneDep = hitInfo.GetTotEneDep();

    actVol = hitInfo.GetActVol();
    outOfWorld = hitInfo.GetOutOfWorld();

    posX = hitInfo.GetPosX();
    posY = hitInfo.GetPosY();
    posZ = hitInfo.GetPosZ();
    verPosX = hitInfo.GetVerPosX();
    verPosY = hitInfo.GetVerPosY();
    verPosZ = hitInfo.GetVerPosZ();

    FillTree();


    /*G4ThreeVector pos;
    G4ThreeVector verPos;*/

}

//
//  Finish
//
void AnalysisManager::HitFinish()
{

}

void AnalysisManager::UpdateScintDim(double x, double y, double z)
{
    char print[50];
    sprintf(print, "%f %f %f cm", x/cm , y/cm, z/cm);
    dimensions->SetString(print);
}

void AnalysisManager::UpdateNumScint(int a, int b, int c)
{
    char print[50];
    sprintf(print, "%d %d %d scint", a , b, c);
    numberOfScint->SetString(print);
}

void AnalysisManager::UpdateDeadLayThic(double x)
{
    char print[50];
    sprintf(print, "%f", x/um);
    deadLayerThic->SetString(print);
}

void AnalysisManager::UpdateGunInfo(int a, int b, int c, int d)
{
    char print[50];
    sprintf(print, "%d %d %d %d", a , b, c, d);
    gunInfo->SetString(print);
}

void AnalysisManager::SaveRunInfo()
{
    hitTree->GetUserInfo()->Add(dimensions);
    hitTree->GetUserInfo()->Add(numberOfScint);
    hitTree->GetUserInfo()->Add(deadLayerThic);
    hitTree->GetUserInfo()->Add(gunInfo);
}
