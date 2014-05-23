#ifndef Ex02StripParameterisation_h
#define Ex02StripParameterisation_h 1

#include "globals.hh"
#include "G4VPVParameterisation.hh"

class G4VPhysicalVolume;
class G4Box;

// Dummy declarations to get rid of warnings ...
class G4Trd;
class G4Trap;
class G4Cons;
class G4Orb;
class G4Sphere;
class G4Ellipsoid;
class G4Torus;
class G4Para;
class G4Hype;
class G4Tubs;
class G4Polycone;
class G4Polyhedra;

///  A parameterisation that describes a series of boxes along Z.
///
///  The boxes have equal width, & their lengths are a linear equation.
///  They are spaced an equal distance apart, starting from given location.

class Ex02StripParameterisation : public G4VPVParameterisation { 
  public:
  
    Ex02StripParameterisation(G4int noStrips, G4double chamberHalfWidthX, G4double chamberHalfWidthY, G4double chamberHalfWidthZ);

    virtual ~Ex02StripParameterisation();
   
    void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume* physVol) const;
    
    void ComputeDimensions(G4Box& stripBox, const G4int copyNo, const G4VPhysicalVolume* physVol) const;

  private:  // Dummy declarations to get rid of warnings ...

    void ComputeDimensions(G4Tubs&,const G4int,const G4VPhysicalVolume*) const {};
    void ComputeDimensions(G4Trd&,const G4int,const G4VPhysicalVolume*) const {};
    void ComputeDimensions(G4Trap&,const G4int,const G4VPhysicalVolume*) const {};
    void ComputeDimensions(G4Cons&,const G4int,const G4VPhysicalVolume*) const {};
    void ComputeDimensions(G4Sphere&,const G4int,const G4VPhysicalVolume*) const {};
    void ComputeDimensions(G4Orb&,const G4int,const G4VPhysicalVolume*) const {};
    void ComputeDimensions(G4Ellipsoid&,const G4int,const G4VPhysicalVolume*) const {};
    void ComputeDimensions(G4Torus&,const G4int,const G4VPhysicalVolume*) const {};
    void ComputeDimensions(G4Para&,const G4int,const G4VPhysicalVolume*) const {};
    void ComputeDimensions(G4Hype&,const G4int,const G4VPhysicalVolume*) const {};
    void ComputeDimensions(G4Polycone&,const G4int,const G4VPhysicalVolume*) const {};
    void ComputeDimensions(G4Polyhedra&,const G4int,const G4VPhysicalVolume*) const {};

  private:

    G4int    fNoStrips;
    G4double fStartX;
    G4double fStartZ;
    G4double fEndZ;
    G4double fSpacing;
    G4double fHalfWidthX;
    G4double fHalfWidthY;
    G4double fHalfWidthZ;
};

#endif
