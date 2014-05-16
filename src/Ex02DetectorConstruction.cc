#include "Ex02DetectorConstruction.hh"
#include "Ex02MagneticField.hh"
#include "Ex02TrackerSD.hh"
#include "Ex02MuonModel.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProductionCuts.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"

Ex02DetectorConstruction::Ex02DetectorConstruction() : experimentalHall_log(0), trackerBlock_log(0), trackerLayer_log(0), experimentalHall_phys(0), trackerBlock_phys(0), trackerLayer_phys(0) {
        fpMagField = new Ex02MagneticField();
        fpMagField->SetMagFieldValue(G4ThreeVector(0., 0.01, 0.));
}

Ex02DetectorConstruction::~Ex02DetectorConstruction() {
    delete fpMagField;
}

G4VPhysicalVolume* Ex02DetectorConstruction::Construct() {

    //------------------------------------------------------ materials

    G4double a;  // atomic mass
    G4double z;  // atomic number
    G4double density;

    G4Material* Ar = new G4Material("ArgonGas", z=18., a=39.95*g/mole, density=1.782*mg/cm3);

    G4Material* Al = new G4Material("Aluminum", z=13., a=26.98*g/mole, density=2.7*g/cm3);

    G4Material* Pb = new G4Material("Lead", z=82., a=207.19*g/mole, density=11.35*g/cm3);

    //------------------------------------------------------ volumes

    //------------------------------ experimental hall (world volume)
    //------------------------------ beam line along x axis

    G4double expHall_x = 2.5*m;
    G4double expHall_y = 1.0*m;
    G4double expHall_z = 1.0*m;
    G4Box* experimentalHall_box = new G4Box("expHall_box", expHall_x, expHall_y, expHall_z);
    experimentalHall_log = new G4LogicalVolume(experimentalHall_box, Ar, "expHall_log", 0, 0, 0);
    experimentalHall_phys = new G4PVPlacement(0, G4ThreeVector(), experimentalHall_log, "expHall", 0, false, 0);

    //------------------------------ a tracker block

    G4double block_x = 50.0*cm;
    G4double block_y = 100.0*cm;
    G4double block_z = 100.0*cm;
    G4Box* trackerBlock_box = new G4Box("trackerBlock_box", block_x, block_y, block_z);
    trackerBlock_log = new G4LogicalVolume(trackerBlock_box, Pb, "trackerBlock_log", 0, 0, 0);
    G4double blockPos_x = 2.0*m;
    G4double blockPos_y = 0.0*m;
    G4double blockPos_z = 0.0*m;
    trackerBlock_phys = new G4PVPlacement(0, G4ThreeVector(blockPos_x, blockPos_y, blockPos_z), trackerBlock_log, "trackerBlock", experimentalHall_log, false, 0);

    //------------------------------ tracker layers

    G4double tracker_x = 1.*cm;
    G4double tracker_y = 100.*cm;
    G4double tracker_z = 100.*cm;
    G4Box* trackerLayer_box = new G4Box("trackerLayer_box", tracker_x, tracker_y, tracker_z);
    trackerLayer_log = new G4LogicalVolume(trackerLayer_box, Al, "trackerLayer_log", 0, 0, 0);
    for(G4int i = 0; i < 5; i++)  {
        G4double trackerPos_x = (i-2)*20.*cm;
        G4double trackerPos_y = 0.0*m;
        G4double trackerPos_z = 0.0*m;
        trackerLayer_phys = new G4PVPlacement(0, G4ThreeVector(trackerPos_x, trackerPos_y, trackerPos_z), trackerLayer_log, "trackerLayer", trackerBlock_log, false, i);
    }

    //------------------------------ SD 
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4String trackerSDName = "Ex02/TrackerSD";
    Ex02TrackerSD* trackerSD = new Ex02TrackerSD(trackerSDName);
    SDman->AddNewDetector(trackerSD);
    trackerLayer_log->SetSensitiveDetector(trackerSD);

    G4String ROgeometryName = "TrackerROGeometry";
    G4VReadOutGeometry* trackerRO = new Ex02TrackerROGeometry(ROgeometryName);
    trackerRO->BuildROGeometry();
    trackerSD->SetROgeometry(trackerRO);
    //------------------ Parameterisation Models --------------------------

    G4Region* trackerRegion = new G4Region("tracker_region");
    trackerRegion->AddRootLogicalVolume(trackerLayer_log);
    std::vector<double> cuts; cuts.push_back(1.0*mm);cuts.push_back(1.0*mm);cuts.push_back(1.0*mm);
    trackerRegion->SetProductionCuts(new G4ProductionCuts());
    trackerRegion->GetProductionCuts()->SetProductionCuts(cuts);
    new Ex02MuonModel("MuonModel", trackerRegion); 


    //------------------------------ Visualisaion
    G4VisAttributes* BoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    experimentalHall_log->SetVisAttributes(BoxVisAtt);
    trackerBlock_log->SetVisAttributes(BoxVisAtt);

    G4VisAttributes* ChamberVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
    trackerLayer_log->SetVisAttributes(ChamberVisAtt);
    //------------------------------------------------------------------

    return experimentalHall_phys;
}

void Ex02DetectorConstruction::SetMagField(G4double fieldValue) {
    fpMagField->SetMagFieldValue(fieldValue);
}
