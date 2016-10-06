#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "RunAction.hh"
#include "globals.hh"
#include "ExN01DetectorConstruction.hh"

class EventAction : public G4UserEventAction
{
 public:

    EventAction(RunAction *, ExN01DetectorConstruction*);
    ~EventAction();

    void BeginOfEventAction(const G4Event *);
    void EndOfEventAction(const G4Event *);

 private:

    ExN01DetectorConstruction* det;

};

#endif // EVENTACTION_HH
