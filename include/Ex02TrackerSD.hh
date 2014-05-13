
#ifndef Ex02TrackerSD_h
#define Ex02TrackerSD_h 1

#include "G4VSensitiveDetector.hh"
#include "Ex02TrackerHit.hh"

class G4Step;
class G4HCofThisEvent;

class Ex02TrackerSD : public G4VSensitiveDetector {
  public:
      Ex02TrackerSD(G4String);
     ~Ex02TrackerSD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);

  private:
      Ex02TrackerHitsCollection* trackerCollection;

};

#endif

