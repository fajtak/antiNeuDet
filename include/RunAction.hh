#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "globals.hh"
#include "ExN01DetectorConstruction.hh"

class RunAction : public G4UserRunAction
{
 public:

   RunAction(ExN01DetectorConstruction*);
   ~RunAction();

   void BeginOfRunAction(const G4Run *);
   void EndOfRunAction(const G4Run *);

   G4int RunID();

 private:

    G4int runID;
    ExN01DetectorConstruction* det;

};

#endif // RUNACTION_HH
