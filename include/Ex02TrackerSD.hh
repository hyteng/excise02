
#ifndef Ex02TrackerSD_h
#define Ex02TrackerSD_h 1

#include "G4VSensitiveDetector.hh"
#include "Ex02TrackerHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class Ex02TrackerSD : public G4VSensitiveDetector {
  public:
      Ex02TrackerSD(G4String, G4double, G4bool);
     ~Ex02TrackerSD();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);

  private:
      Ex02TrackerHitsCollection* trackerCollection;
      G4int tracker[5][400];
      G4double efficiency;
      G4bool addNoise;
};

#endif

