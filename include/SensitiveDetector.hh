#ifndef SENSITIVEDETECTOR_HH
#define SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4TouchableHistory.hh"
#include "G4VVisManager.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "ExN01TrackerHit.hh"


class G4Step;
class G4HCofThisEvent;
class ExN01TrackerHit;

class SensitiveDetector : public G4VSensitiveDetector {

 public:

    SensitiveDetector(G4String);
    ~SensitiveDetector();

    void Initialize(G4HCofThisEvent *);
    G4bool ProcessHits(G4Step *, G4TouchableHistory *);
    void EndOfEvent(G4HCofThisEvent *);

    void SetRunID(G4int newValue){hitInfo.SetRunID(newValue);};
    void SetEveID(G4int newValue){hitInfo.SetEveID(newValue);};

 private:
    ExN01TrackerHit hitInfo;

};

#endif // SENSITIVEDETECTOR_HH
