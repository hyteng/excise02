#ifndef Ex02SimpleSolenoidPart_H
#define Ex02SimpleSolenoidPart_H 1

#include "G4MagneticField.hh"

#include "G4TransportationManager.hh"
#include "G4Navigator.hh"
#include "G4LogicalVolume.hh"
#include "G4FieldManager.hh"
#include "geomdefs.hh"
#include "globals.hh"

class Ex02SimpleSolenoidPart : public G4MagneticField {

    public:

        Ex02SimpleSolenoidPart(G4ThreeVector B, G4LogicalVolume* lv, G4ThreeVector c);  //  The value of the field
        Ex02SimpleSolenoidPart();               //  A zero field
        virtual ~Ex02SimpleSolenoidPart();  

        //virtual G4bool DoesFieldChangeEnergy () const {return false;};
        //void Construct();
        void SetMagFieldValue(G4ThreeVector fieldVector);
        virtual void GetFieldValue(const G4double* point, G4double* field) const;

    protected:

        // Find the global Field Manager
        G4FieldManager* GetGlobalFieldManager();   // static 

    private:

        EInside GetSide(G4ThreeVector& local) const;

        G4LogicalVolume* SolenoidPart;
        G4ThreeVector globalCenter;
        G4ThreeVector localBField;

        static G4AffineTransform global2local;
        static G4Navigator* aNavigator;
        static G4bool TopTransformSet;
};

#endif
