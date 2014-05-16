#include "ExN04CalorimeterROGeometry.hh"

ExN04CalorimeterROGeometry::ExN04CalorimeterROGeometry() : G4VReadOutGeometry() {
}

ExN04CalorimeterROGeometry::ExN04CalorimeterROGeometry(G4String aString) : G4VReadOutGeometry(aString), dummyMat(0) {
}

ExN04CalorimeterROGeometry::~ExN04CalorimeterROGeometry() {
}

G4VPhysicalVolume* ExN04CalorimeterROGeometry::Build() {

    G4Material* dummyMat  = new G4Material(name="dummyMat", 1., 1.*g/mole, 1.*g/cm3);

    G4double expHall_x = 2.5*m;
    G4double expHall_y = 1.0*m;
    G4double expHall_z = 1.0*m;
    G4Box* experimentalHall_box = new G4Box("expHall_box", expHall_x, expHall_y, expHall_z);
    G4LogicalVolume* experimentalHall_log = new G4LogicalVolume(experimentalHall_box, dummyMat, "expHall_log", 0, 0, 0);
    G4VPhysicalVolume* experimentalHall_phys = new G4PVPlacement(0, G4ThreeVector(), experimentalHall_log, "expHall", 0, false, 0);

    //------------------------------ a tracker block

    G4double block_x = 50.0*cm;
    G4double block_y = 100.0*cm;
    G4double block_z = 100.0*cm;
    G4Box* trackerBlock_box = new G4Box("trackerBlock_box", block_x, block_y, block_z);
    G4LogicalVolume* trackerBlock_log = new G4LogicalVolume(trackerBlock_box, dummyMat, "trackerBlock_log", 0, 0, 0);
    G4double blockPos_x = 2.0*m;
    G4double blockPos_y = 0.0*m;
    G4double blockPos_z = 0.0*m;
    G4VPhysicalVolume* trackerBlock_phys = new G4PVPlacement(0, G4ThreeVector(blockPos_x, blockPos_y, blockPos_z), trackerBlock_log, "trackerBlock", experimentalHall_log, false, 0);

    //------------------------------ tracker layers

    G4double tracker_x = 1.*cm;
    G4double tracker_y = 100.*cm;
    G4double tracker_z = 100.*cm;
    G4Box* trackerLayer_box = new G4Box("trackerLayer_box", tracker_x, tracker_y, tracker_z);
    G4LogicalVolume* trackerLayer_log = new G4LogicalVolume(trackerLayer_box, dummyMat, "trackerLayer_log", 0, 0, 0);
    for(G4int i = 0; i < 5; i++)  {
        G4double trackerPos_x = (i-2)*20.*cm;
        G4double trackerPos_y = 0.0*m;
        G4double trackerPos_z = 0.0*m;
        G4VPhysicalVolume* trackerLayer_phys = new G4PVPlacement(0, G4ThreeVector(trackerPos_x, trackerPos_y, trackerPos_z), trackerLayer_log, "trackerLayer", trackerBlock_log, false, i);
    }

    //------------------------------ Strips
    G4double strip_x = 1.*mm;
    G4double strip_y = 100.*cm;
    G4double strip_z = 1.5*cm;
    G4Box* strip= new G4Box("strip_box", strip_x, strip_y, strip_z);
    G4LogicalVolume* strip_log = new G4LogicalVolume(strip_box, dummyMat, "strip_log", 0, 0, 0);
    for(G4int j = 0; j < 40; i++)  {
        G4double stripPos_x = 0.*mm;
        G4double stripPos_y = 0.*mm;
        G4double stripPos_z = -tracker_z+2.5*cm+j*5.0*cm;
        G4VPhysicalVolume* strip_phys = new G4PVPlacement(0, G4ThreeVector(stripPos_x, stripPos_y, stripPos_z), strip_log, "strip", trackerLayer_log, false, j);
    }

    return experimentalHall_phys;
}
