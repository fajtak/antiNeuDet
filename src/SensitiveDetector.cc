#include "SensitiveDetector.hh"
#include "ExN01PrimaryGeneratorAction.hh"
#include "ExN01TrackerHit.hh"
#include "AnalysisManager.hh"

#include "G4ThreeVector.hh"
#include "G4VProcess.hh"
#include "globals.hh"


//
// Constructor
//
SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name) {}

//
// Destructor
//
SensitiveDetector::~SensitiveDetector() {}

//
// This method is called at the beginning of each event for each sensitive detector
//
void SensitiveDetector::Initialize(G4HCofThisEvent *){

}

//
// Called by SteppingManager when a step is performed in Logical volume (sensitive)
//
G4bool SensitiveDetector::ProcessHits(G4Step * aStep, G4TouchableHistory *)
{
    hitInfo.SetActVol(true);

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

    G4TouchableHistory* stepTouchHist = (G4TouchableHistory*)(preStepPoint->GetTouchable());
    // Obtain a replica number of individual ecal layers ( "" ... current vol, "1" ... mother vol, ...)
    hitInfo.SetRepNSci(stepTouchHist->GetReplicaNumber(1));
    hitInfo.SetRepNSta(stepTouchHist->GetReplicaNumber(3));

    G4String layerID = stepTouchHist->GetVolume(2)->GetName();
    if (layerID == "Layer1") hitInfo.SetLayID(1);
    if (layerID == "Layer2") hitInfo.SetLayID(2);

    if (posStepPoint->GetProcessDefinedStep() != 0)
        hitInfo.SetStePro(posStepPoint->GetProcessDefinedStep()->GetProcessName());
    else
        hitInfo.SetStePro("UserLimit");

    hitInfo.SetOutOfWorld(false);

    AnalysisManager* analysis = AnalysisManager::GetInstance(); // singleton
    analysis -> HitProcess(hitInfo);

    G4VPhysicalVolume* physVol = preStepPoint->GetPhysicalVolume();
    const G4VTouchable* touchable = preStepPoint->GetTouchable();
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if((pVVisManager)&&(aStep->GetTotalEnergyDeposit()/MeV > 0.01)){//Make sure that the VisManager exists
        G4VisAttributes attribs(G4Colour(1.,0.,0.));
        attribs.SetForceSolid(true);
        G4RotationMatrix rot;
        if(touchable->GetRotation())//If a rotation is defined use it
        rot=*(touchable->GetRotation());
        G4Transform3D trans(rot,touchable->GetTranslation());//Create transform
        pVVisManager->Draw(*physVol,attribs,trans);//Draw it
    }

    //hitInfo.Print(6);
    return true;
}

//
// This method is called at the end of each event for each sensitive detector
//
void SensitiveDetector::EndOfEvent(G4HCofThisEvent*) {


}
