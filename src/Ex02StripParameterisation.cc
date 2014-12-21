#include "Ex02StripParameterisation.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Box.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

Ex02StripParameterisation::Ex02StripParameterisation(G4int noStrips, G4double chamberHalfWidthX, G4double chamberHalfWidthY, G4double chamberHalfWidthZ) : G4VPVParameterisation() {

    fNoStrips = noStrips;
    if(fNoStrips > 0)
        fSpacing = 2.0*chamberHalfWidthZ/(double)fNoStrips;
    else
        fSpacing = 2.0*chamberHalfWidthZ;
    fStartZ = fSpacing*0.5-chamberHalfWidthZ;
    fEndZ = chamberHalfWidthZ-fSpacing*0.5;
    fStartX = chamberHalfWidthX*(0.1-1.0);
    fHalfWidthX = chamberHalfWidthX*0.05;
    fHalfWidthY = chamberHalfWidthY*0.9;
    fHalfWidthZ = fSpacing*0.4;
}

Ex02StripParameterisation::~Ex02StripParameterisation() { 
}

void Ex02StripParameterisation::ComputeTransformation(const G4int copyNo, G4VPhysicalVolume* physVol) const {

    G4double xPos = fStartX;
    G4double yPos = 0.;
    G4double zPos = fStartZ+copyNo*fSpacing;
    G4ThreeVector origin(xPos, yPos, zPos);
    physVol->SetTranslation(origin);
    physVol->SetRotation(0);
    G4cout << "Translation: " << origin << G4endl;
}

void Ex02StripParameterisation::ComputeDimensions(G4Box& stripBox, const G4int copyNo, const G4VPhysicalVolume* physVol) const {
    stripBox.SetXHalfLength(fHalfWidthX);
    stripBox.SetYHalfLength(fHalfWidthY);
    stripBox.SetZHalfLength(fHalfWidthZ);
}
