#ifndef Ex02TrackDigitizer_h
#define Ex02TrackDigitizer_h 1

#include "G4VDigitizerModule.hh"
#include "Ex02TrackDigi.hh"
#include "globals.hh"

class Ex02TrackDigitizer : public G4VDigitizerModule {

    public:
        Ex02TrackDigitizer(G4String name);
        ~Ex02TrackDigitizer();
    
        void Digitize();

    private:
        Ex02TrackDigitsCollection*  DigitsCollection;
};

#endif
