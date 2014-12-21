#ifndef Ex02TrackerDigitizer_h
#define Ex02TrackerDigitizer_h 1

#include "G4VDigitizerModule.hh"
#include "Ex02TrackerDigi.hh"
#include "globals.hh"

class Ex02TrackerDigitizer : public G4VDigitizerModule {

    public:
        Ex02TrackerDigitizer(G4String name);
        ~Ex02TrackerDigitizer();
    
        inline void SetRunNumber(G4int n) {RunNumber = n;};
        inline G4int GetRunNumber() {return RunNumber;};
        inline void SetEventNumber(G4int n) {EventNumber = n;};
        inline G4int GetEventNumber() {return EventNumber;};
        void Digitize();

    private:
        Ex02TrackerDigitsCollection*  DigitsCollection;
        G4int EventNumber;
        G4int RunNumber;
};

#endif
