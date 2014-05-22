#ifndef Ex02DummySD_h
#define Ex02DummySD_h 1

#include "G4VSensitiveDetector.hh"
class G4Step;

class Ex02DummySD : public G4VSensitiveDetector {

    public:
        Ex02DummySD();
        ~Ex02DummySD() {}

        void Initialize(G4HCofThisEvent*) {}
        G4bool ProcessHits(G4Step*, G4TouchableHistory*) {return false;}
        void EndOfEvent(G4HCofThisEvent*) {}
        void clear() {}
        void DrawAll() {}
        void PrintAll() {}
};

Ex02DummySD::Ex02DummySD() : G4VSensitiveDetector("dummySD") {
}

#endif
