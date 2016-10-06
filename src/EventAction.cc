#include "EventAction.hh"
#include "AnalysisManager.hh"

//
// Constructor
//
EventAction::EventAction(RunAction*, ExN01DetectorConstruction* myDet) : det(myDet)
{}

//
// Destructor
//
EventAction::~EventAction() {}

//
// This method is called at the beginning of each EVENT
//
void EventAction::BeginOfEventAction(const G4Event * anEvent)
{
// Info output
   G4int EvtID = anEvent -> GetEventID() + 1;
   if ((EvtID%10000)==0) G4cout << "Event number " << EvtID << G4endl;

// Initialize digitization
   AnalysisManager * analysis = AnalysisManager::GetInstance();
   analysis -> HitInit();
   analysis -> SetEventID(anEvent -> GetEventID());
}

void EventAction::EndOfEventAction(const G4Event * anEvent )
{
// Save an event ID, finish digitization and fill the data to an ntuple
   AnalysisManager * analysis = AnalysisManager::GetInstance();
   analysis -> HitFinish();
   analysis -> FillNtupleE();
   analysis -> FillNtupleN();
}


