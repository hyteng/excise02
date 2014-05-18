#ifndef Ex02TrackerDigi_h 
#define Ex02TrackerDigi_h 1

#include "G4VDigi.hh"
#include "G4TDigiCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class Ex02TrackerDigi : public G4VDigi {

    public:
        Ex02TrackerDigi();
        Ex02TrackerDigi(const Ex02TrackerDigi&);
        ~Ex02TrackerDigi();
        const Ex02TrackerDigi& operator=(const Ex02TrackerDigi&);
        int operator==(const Ex02TrackerDigi&) const;
        
        inline void* operator new(size_t);
        inline void  operator delete(void*);

        void Draw();
        void Print();
  
        inline void SetDetector(const G4int & DN) {DetectorNumber = DN;};
        inline G4int GetDetector() {return DetectorNumber;};
        inline void SetStrip(const G4int & StripNb) {StripNumber = StripNb;};
        inline G4int GetStrip() {return StripNumber;};
        inline void SetPosition(const G4ThreeVector & thePosition) {GlobalPosition = thePosition;} ;
        inline G4ThreeVector GetPosition() {return GlobalPosition;};
        inline void SetError(const G4ThreeVector & theError) {GlobalError = theError;};
        inline G4ThreeVector GetError() {return GlobalError;};
        inline void SetSimPosition(const G4ThreeVector & theSimPosition) {GlobalSimPosition = theSimPosition;} ;
        inline G4ThreeVector GetSimPosition() {return GlobalSimPosition;};

    private:
        G4int DetectorNumber;
        G4int StripNumber;
        G4ThreeVector GlobalPosition;
        G4ThreeVector GlobalError;
        G4ThreeVector GlobalSimPosition;
};


typedef G4TDigiCollection<Ex02TrackerDigi> Ex02TrackerDigitsCollection;

extern G4Allocator<Ex02TrackerDigi> Ex02TrackerDigiAllocator;

inline void* Ex02TrackerDigi::operator new(size_t) {

    void *aDigi = (void*) Ex02TrackerDigiAllocator.MallocSingle();
    return aDigi;
}

inline void Ex02TrackerDigi::operator delete(void* aDigi) {
    Ex02TrackerDigiAllocator.FreeSingle((Ex02TrackerDigi*) aDigi);
}
#endif
