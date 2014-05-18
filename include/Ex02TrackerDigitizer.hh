#ifndef Ex02TrackerDigitizer_h
#define Ex02TrackerDigitizer_h 1

#include "G4VDigitizerModule.hh"
#include "Ex02TrackerDigi.hh"
#include "globals.hh"

class Ex02TrackerDigitizer : public G4VDigitizerModule {

    public:
        Ex02TrackerDigitizer(G4String name);
        ~Ex02TrackerDigitizer();
    
        void Digitize();

    private:
        Ex02TrackerDigitsCollection*  DigitsCollection;
};

#endif
