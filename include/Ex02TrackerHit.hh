
#ifndef Ex02TrackerHit_h
#define Ex02TrackerHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"


class Ex02TrackerHit : public G4VHit {
    public:

        Ex02TrackerHit();
        ~Ex02TrackerHit();
        Ex02TrackerHit(const Ex02TrackerHit&);
        const Ex02TrackerHit& operator=(const Ex02TrackerHit&);
        G4int operator==(const Ex02TrackerHit&) const;

        inline void* operator new(size_t);
        inline void  operator delete(void*);

        void Draw();
        void Print();

    public:

        void SetTrackID  (G4int track)      { trackID = track; };
        void SetChamberNb(G4int chamb)      { chamberNb = chamb; };
        void SetStrip    (G4int st)         {strip = st};
        void SetEdep     (G4double de)      { edep = de; };
        void SetHitPos   (G4ThreeVector x)  { hitPos = x; };
        void SetHitPos   (G4ThreeVector y)  { digiPos = y; };
        void SetError   (G4ThreeVector z)  { error = z; };

        G4int GetTrackID()          { return trackID; };
        G4int GetChamberNb()        { return chamberNb; };
        G4int GetStrip()            { return strip; };
        G4double GetEdep()          { return edep; };      
        G4ThreeVector GetHitPos()   { return hitPos; };
        G4ThreeVector GetDigiPos()  { return digiPos; };
        G4ThreeVector GetError()    { return error; };
        

    private:

        G4int         trackID;
        G4int         chamberNb;
        G4int         strip;
        G4double      edep;
        G4ThreeVector hitPos;
        G4ThreeVector digiPos;
        G4ThreeVector error;
        
};

typedef G4THitsCollection<Ex02TrackerHit> Ex02TrackerHitsCollection;

extern G4Allocator<Ex02TrackerHit> Ex02TrackerHitAllocator;

inline void* Ex02TrackerHit::operator new(size_t) {

    void *aHit;
    aHit = (void *) Ex02TrackerHitAllocator.MallocSingle();
    return aHit;
}


inline void Ex02TrackerHit::operator delete(void *aHit) {

    Ex02TrackerHitAllocator.FreeSingle((Ex02TrackerHit*) aHit);
}


#endif
