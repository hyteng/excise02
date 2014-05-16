#ifndef Ex02TrackDigi_h 
#define Ex02TrackDigi_h 1

#include "G4VDigi.hh"
#include "G4TDigiCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class Ex02TrackDigi : public G4VDigi {

    public:
        Ex02TrackDigi();
        Ex02TrackDigi(const Ex02TrackDigi&);
        ~Ex02TrackDigi();
        const Ex02TrackDigi& operator=(const Ex02TrackDigi&);
        int operator==(const Ex02TrackDigi&) const;
        
        inline void* operator new(size_t);
        inline void  operator delete(void*);

        void Draw();
        void Print();
  
        inline void SetPosition(const G4ThreeVector & thePosition) {GlobalPosition = thePosition} ;
        inline G4ThreeVector GetPosition() {return GlobalPosition};
        inline void SetError(const G4ThreeVector & theError) {GlobalError = theError};
        inline G4ThreeVector GetError() {return GlobalError};

    private:
        G4int DetectorNumber;
        G4int StripNumber;
        G4ThreeVector GlobalPosition;
        G4ThreeVector GlobalError;
};
