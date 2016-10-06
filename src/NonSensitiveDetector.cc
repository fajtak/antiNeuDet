#include "NonSensitiveDetector.hh"
#include "ExN01PrimaryGeneratorAction.hh"
#include "AnalysisManager.hh"

#include "G4ThreeVector.hh"
#include "G4VProcess.hh"
#include "globals.hh"


//
// Constructor
//
NonSensitiveDetector::NonSensitiveDetector(G4String name) : G4VSensitiveDetector(name) {}

//
// Destructor
//
NonSensitiveDetector::~NonSensitiveDetector() {}

//
// This method is called at the beginning of each event for each sensitive detector
//
void NonSensitiveDetector::Initialize(G4HCofThisEvent *){
}

//
// Called by SteppingManager when a step is performed in Logical volume (sensitive)
//
G4bool NonSensitiveDetector::ProcessHits(G4Step * aStep, G4TouchableHistory *)
{
    hitInfo.SetActVol(false);

    G4Track* aTrack = aStep->GetTrack();
    hitInfo.SetTraID(aTrack->GetTrackID());
    hitInfo.SetParID(aTrack->GetParentID());
    hitInfo.SetSteID(aTrack->GetCurrentStepNumber());

    hitInfo.SetParNam(aTrack->GetDefinition()->GetParticleName());
    hitInfo.SetPDGenc(aTrack->GetDefinition()->GetPDGEncoding());

    hitInfo.SetGloTim(aTrack->GetGlobalTime()/microsecond);

    hitInfo.SetKinEne(aTrack -> GetKineticEnergy()/MeV);
    hitInfo.SetTraLen(aTrack->GetTrackLength()/mm);
    hitInfo.SetVerPos(aTrack->GetVertexPosition());
    hitInfo.SetPos(aTrack->GetPosition());
    hitInfo.SetVerKinEne(aTrack->GetVertexKineticEnergy()/MeV);

    if (aTrack -> GetCreatorProcess() != NULL)
        hitInfo.SetCrePro(aTrack->GetCreatorProcess()->GetProcessName());
    else
        hitInfo.SetCrePro("InitStep");

    hitInfo.SetTotEneDep(aStep->GetTotalEnergyDeposit()/MeV);
    hitInfo.SetSteLen(aStep->GetStepLength()/mm);

    G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint* posStepPoint = aStep->GetPostStepPoint();

    if (preStepPoint->GetPhysicalVolume()->GetName() != "expHall"){
        G4TouchableHistory* stepTouchHist = (G4TouchableHistory*)(preStepPoint->GetTouchable());
        // Obtain a replica number of individual ecal layers ( "" ... current vol, "1" ... mother vol, ...)
        hitInfo.SetRepNSci(stepTouchHist->GetReplicaNumber());
        hitInfo.SetRepNSta(stepTouchHist->GetReplicaNumber(2));

        G4String layerID = stepTouchHist->GetVolume(1)->GetName();
        if (layerID == "Layer1") hitInfo.SetLayID(1);
        if (layerID == "Layer2") hitInfo.SetLayID(2);

    }else{

        hitInfo.SetRepNSci(-1);
        hitInfo.SetRepNSta(-1);
        hitInfo.SetLayID(-1);
        if (aTrack->GetNextVolume() == 0)
            hitInfo.SetOutOfWorld(true);

    }

    hitInfo.SetDeaLayNam(preStepPoint->GetPhysicalVolume()->GetName());

    if (posStepPoint->GetProcessDefinedStep() != 0)
        hitInfo.SetStePro(posStepPoint->GetProcessDefinedStep()->GetProcessName());
    else
        hitInfo.SetStePro("UserLimit");


    AnalysisManager* analysis = AnalysisManager::GetInstance(); // singleton
    analysis -> HitProcess(hitInfo);

    //hitInfo.Print(6);
    return true;
}

//
// This method is called at the end of each event for each sensitive detector
//
void NonSensitiveDetector::EndOfEvent(G4HCofThisEvent*) {}
