#ifndef Ex02TrackerROGeometry_h
#define Ex02TrackerROGeometry_h 1

#include "G4VReadOutGeometry.hh"

class Ex02TrackerROGeometry : public G4VReadOutGeometry {
    
    public:
        Ex02TrackerROGeometry(G4int);
        Ex02TrackerROGeometry(G4String, G4int);
        ~Ex02TrackerROGeometry();
        void SetStripNumber(G4int n);

    private:
        G4VPhysicalVolume* Build();
        G4Material* dummyMat;

        G4bool fCheckOverlaps;
        G4int NbOfStrips;
};

#endif
