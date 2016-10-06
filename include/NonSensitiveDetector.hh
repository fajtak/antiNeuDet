#ifndef NONSENSITIVEDETECTOR_HH
#define NONSENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4TouchableHistory.hh"
#include "globals.hh"
#include "ExN01TrackerHit.hh"

class G4Step;
class G4HCofThisEvent;
class ExN01TrackerHit;

class NonSensitiveDetector : public G4VSensitiveDetector {

 public:

    NonSensitiveDetector(G4String);
    ~NonSensitiveDetector();

    void Initialize(G4HCofThisEvent *);
    G4bool ProcessHits(G4Step *, G4TouchableHistory *);
    void EndOfEvent(G4HCofThisEvent *);

    void SetRunID(G4int newValue){hitInfo.SetRunID(newValue);};
    void SetEveID(G4int newValue){hitInfo.SetEveID(newValue);};

 private:
    ExN01TrackerHit hitInfo;

};

#endif // NONSENSITIVEDETECTOR_HH
