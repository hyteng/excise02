#include "Ex02TrackerROGeometry.hh"
#include "Ex02StripParameterisation.hh"
#include "Ex02DummySD.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4PVParameterised.hh"
#include "G4GeometryManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"


Ex02TrackerROGeometry::Ex02TrackerROGeometry(G4int n) : G4VReadOutGeometry(), dummyMat(0), fCheckOverlaps(false), NbOfStrips(n) {
}

Ex02TrackerROGeometry::Ex02TrackerROGeometry(G4String aString, G4int n) : G4VReadOutGeometry(aString), dummyMat(0), fCheckOverlaps(false), NbOfStrips(n) {
}

Ex02TrackerROGeometry::~Ex02TrackerROGeometry() {
}

void Ex02TrackerROGeometry::SetStripNumber(G4int n) {
    NbOfStrips = n;
    G4cout << "TrackerRO set Strips: " << NbOfStrips << G4endl;
}

G4VPhysicalVolume* Ex02TrackerROGeometry::Build() {

    dummyMat  = new G4Material(name="dummyMat", 1., 1.*g/mole, 1.*g/cm3);

    G4double expHall_x = 1.0*m;
    G4double expHall_y = 1.0*m;
    G4double expHall_z = 1.0*m;
    G4Box* experimentalHall_box = new G4Box("expHall_box", expHall_x, expHall_y, expHall_z);
    G4LogicalVolume* experimentalHall_log = new G4LogicalVolume(experimentalHall_box, dummyMat, "expHall_log", 0, 0, 0);
    G4VPhysicalVolume* experimentalHall_phys = new G4PVPlacement(0, G4ThreeVector(), experimentalHall_log, "expHall", 0, false, 0);

    //------------------------------ a solenoid block
    G4double part_x = 50.0*cm;
    G4double part_y = 100.0*cm;
    G4double part_z = 100.0*cm;
    G4Box* solenoidPart_box = new G4Box("solenoidPart_box", part_x, part_y, part_z);
    G4LogicalVolume* solenoidPart_log = new G4LogicalVolume(solenoidPart_box, dummyMat, "solenoidPart_log", 0, 0, 0);
    G4double partPos_x = -0.5*m;
    G4double partPos_y = 0.0*m;
    G4double partPos_z = 0.0*m;
    G4VPhysicalVolume* solenoidPart_phys = new G4PVPlacement(0, G4ThreeVector(partPos_x, partPos_y, partPos_z), solenoidPart_log, "solenoidPart", experimentalHall_log, false, 0);

    //------------------------------ a tracker block
    G4double block_x = 50.0*cm;
    G4double block_y = 100.0*cm;
    G4double block_z = 100.0*cm;
    G4Box* trackerBlock_box = new G4Box("trackerBlock_box", block_x, block_y, block_z);
    G4LogicalVolume* trackerBlock_log = new G4LogicalVolume(trackerBlock_box, dummyMat, "trackerBlock_log", 0, 0, 0);
    G4double blockPos_x = 0.5*m;
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
    G4double strip_x = 0.5*mm;
    G4double strip_y = 100.*cm;
    G4double strip_z = tracker_z/NbOfStrips;
    G4Box* strip_box = new G4Box("strip_box", strip_x, strip_y, strip_z);
    G4LogicalVolume* strip_log = new G4LogicalVolume(strip_box, dummyMat, "strip_log", 0, 0, 0);
    
    for(G4int j = 0; j < NbOfStrips; j++)  {
        G4double stripPos_x = 0.*mm;
        G4double stripPos_y = 0.*mm;
        G4double stripPos_z = -tracker_z+j*strip_z*2.0+strip_z;
        G4VPhysicalVolume* strip_phys = new G4PVPlacement(0, G4ThreeVector(stripPos_x, stripPos_y, stripPos_z), strip_log, "strip", trackerLayer_log, false, j);
    }
    /*
    if(NbOfStrips <= 0) {
        G4cout << "NoStrips < 0 " << G4endl;
        return experimentalHall_phys;
    }
    G4cout << "NoStrips: " << NbOfStrips << G4endl;
    G4VPVParameterisation* stripParam = new Ex02StripParameterisation(NbOfStrips, tracker_x, tracker_y, tracker_z);
    G4cout << "NoStrips: " << NbOfStrips << G4endl;
    new G4PVParameterised("strip_log", strip_log, trackerLayer_log, kUndefined, NbOfStrips, stripParam, true);
    */
    G4cout << "NoStrips: " << trackerLayer_log->GetNoDaughters() << G4endl;

    Ex02DummySD * dummySensi = new Ex02DummySD;
    trackerLayer_log->SetSensitiveDetector(dummySensi);

    return experimentalHall_phys;
}
