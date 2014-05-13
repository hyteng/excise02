
#ifndef Ex02MagneticField_H
#define Ex02MagneticField_H

#include "G4UniformMagField.hh"

class G4FieldManager;

class Ex02MagneticField: public G4UniformMagField {
    public:

        Ex02MagneticField(G4ThreeVector);  //  The value of the field
        Ex02MagneticField();               //  A zero field
        ~Ex02MagneticField();  

        //Set the field (fieldValue,0,0)
        void SetMagFieldValue(G4double fieldValue);
        void SetMagFieldValue(G4ThreeVector fieldVector);

        G4ThreeVector GetConstantFieldValue();

    protected:

        // Find the global Field Manager
        G4FieldManager* GetGlobalFieldManager();   // static 
};

#endif
