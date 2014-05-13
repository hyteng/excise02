
#include "Ex02MagneticField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

Ex02MagneticField::Ex02MagneticField() : G4UniformMagField(G4ThreeVector()) {
    GetGlobalFieldManager()->SetDetectorField(this);
    GetGlobalFieldManager()->CreateChordFinder(this);
}


Ex02MagneticField::Ex02MagneticField(G4ThreeVector fieldVector) : G4UniformMagField(fieldVector) {
    GetGlobalFieldManager()->SetDetectorField(this);    
    GetGlobalFieldManager()->CreateChordFinder(this);
}


Ex02MagneticField::~Ex02MagneticField() {
}


// Set the value of the Global Field to fieldValue along X
//
void Ex02MagneticField::SetMagFieldValue(G4double fieldValue) {
    SetMagFieldValue(G4ThreeVector(fieldValue,0,0));
}


// Set the value of the Global Field
//
void Ex02MagneticField::SetMagFieldValue(G4ThreeVector fieldVector) {
    // Find the Field Manager for the global field
    G4FieldManager* fieldMgr = GetGlobalFieldManager();

    if(fieldVector!=G4ThreeVector(0.,0.,0.)) { 
        SetFieldValue(fieldVector);
        fieldMgr->SetDetectorField(this);
        fieldMgr->CreateChordFinder(this);
    } else {
        // If the new field's value is Zero, then it is best to
        //  insure that it is not used for propagation.
        G4MagneticField* magField = 0;
        fieldMgr->SetDetectorField(magField);
    }
}


G4FieldManager*  Ex02MagneticField::GetGlobalFieldManager() {
    return G4TransportationManager::GetTransportationManager()->GetFieldManager();
}

