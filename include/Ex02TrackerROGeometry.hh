#ifndef Ex02TrackerROGeometry_h
#define Ex02TrackerROGeometry_h 1

#include "G4VReadOutGeometry.hh"

class Ex02TrackerROGeometry : public G4VReadOutGeometry {
    
    public:
        Ex02TrackerROGeometry();
        Ex02TrackerROGeometry(G4String);
        ~Ex02TrackerROGeometry();
    private:
        G4VPhysicalVolume* Build();
        G4Material* dummyMat;
};

#endif
