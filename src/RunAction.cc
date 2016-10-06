#include "RunAction.hh"
#include "AnalysisManager.hh"

//
// Constructor
//
RunAction::RunAction(ExN01DetectorConstruction* myDet) : det(myDet) {}

//
// Destructor
//
RunAction::~RunAction() {}

//
// This method is called at the beginning of the "BeamOn() method" (RUN)
//
void RunAction::BeginOfRunAction(const G4Run * aRun){

    // Create singleton AnalysisManager and book ROOT Tree ...
    AnalysisManager * analysis = AnalysisManager::GetInstance();
    analysis -> AMSetup();
    analysis -> BookNtuple();
    analysis -> SetRunID(aRun->GetRunID());

    // Info output
    G4cout << ">>> Run number " << aRun->GetRunID()+1 << " has started. <<<" << G4endl;
    G4cout << "" << G4endl;
    runID = aRun->GetRunID();
}

//
// This method is called at the end of the RUN
//
void RunAction::EndOfRunAction(const G4Run * aRun){

    // Info output
    G4cout << "" << G4endl;
    G4cout << ">>> Run number " << aRun->GetRunID()+1 << " has finished. <<<" << G4endl;
    G4cout << "" << G4endl;

    // Finish work with singleton AnalysisManager and delete it
    AnalysisManager * analysis = AnalysisManager::GetInstance();
    analysis->SaveRunInfo();
    analysis -> SaveNtuple();
    analysis -> AMDelete();
    //delete analysis;
    //analysis = 0;

    // Info output
    G4cout << "Total number of events = " << aRun->GetNumberOfEvent() << G4endl;
    G4cout << "" << G4endl;
}

G4int RunAction::RunID(){

    return runID;

}
