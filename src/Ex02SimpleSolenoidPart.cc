#include "Ex02SimpleSolenoidPart.hh"

#include "globals.hh"
#include "G4GeometryManager.hh"
#include "G4ios.hh"

G4Navigator* Ex02SimpleSolenoidPart::aNavigator;
G4AffineTransform Ex02SimpleSolenoidPart::global2local;
G4bool Ex02SimpleSolenoidPart::TopTransformSet=false;

Ex02SimpleSolenoidPart::Ex02SimpleSolenoidPart(G4ThreeVector B, G4LogicalVolume* lv, G4ThreeVector c) : localBField(B), SolenoidPart(lv), globalCenter(c) {

    GetGlobalFieldManager()->SetDetectorField(this);
    GetGlobalFieldManager()->CreateChordFinder(this);
}

Ex02SimpleSolenoidPart::Ex02SimpleSolenoidPart() : localBField(G4ThreeVector(0,0,0)), SolenoidPart(0), globalCenter(G4ThreeVector(0,0,0)) {

    GetGlobalFieldManager()->SetDetectorField(this);
    GetGlobalFieldManager()->CreateChordFinder(this);
}

Ex02SimpleSolenoidPart::~Ex02SimpleSolenoidPart() {
}

void Ex02SimpleSolenoidPart::SetMagFieldValue(G4ThreeVector fieldVector) {
    localBField = fieldVector;
}

void Ex02SimpleSolenoidPart::GetFieldValue(const G4double* point, G4double* field) const {

    G4Navigator* theNavigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
    if(!aNavigator) {
        aNavigator = new G4Navigator();
        if(theNavigator->GetWorldVolume())
            aNavigator->SetWorldVolume(theNavigator->GetWorldVolume());
    }
    //G4cout << "Solenoid Part 1. WorldVolume " << aNavigator->GetWorldVolume()->GetName() << G4endl;

    G4GeometryManager* geomManager = G4GeometryManager::GetInstance();
    if(!geomManager->IsGeometryClosed()) {
        geomManager->OpenGeometry();
        geomManager->CloseGeometry(true);
    }
    //G4cout << "Solenoid Part 2." << G4endl;

    //G4AffineTransform global2local;
    if(aNavigator && TopTransformSet == false) {
        aNavigator->LocateGlobalPointAndSetup(globalCenter,0,false);
        G4TouchableHistoryHandle fTouchable = aNavigator->CreateTouchableHistoryHandle();
        G4int depth = fTouchable->GetHistoryDepth();
        for(G4int i = 0; i<depth; ++i) {
            if(fTouchable->GetVolume()->GetLogicalVolume() == SolenoidPart)
                break;
            fTouchable->MoveUpHistory();
        }
        global2local = fTouchable->GetHistory()->GetTopTransform();
    }
    //G4cout << "Solenoid Part 3." << G4endl;
    
    G4ThreeVector localCenter = global2local.TransformPoint(globalCenter);
    //G4cout << "globalCenter: " << globalCenter << ", localCenter: " << localCenter << G4endl;


    G4ThreeVector globalPos = G4ThreeVector(point[0], point[1], point[2]);
    G4ThreeVector localPos = global2local.TransformPoint(globalPos);
    //G4cout << "globalPos: " << globalPos << ", localPos: " << localPos << G4endl;

    G4double localFieldX = localBField.x();
    G4double localFieldY = localBField.y();
    G4double localFieldZ = localBField.z();
    EInside posSort = GetSide(localPos);
    switch(posSort) {
        case kOutside:
            localFieldX*=-0.5;
            localFieldY*=-0.5;
            localFieldZ*=-0.5;
            break;
        case kSurface:
            localFieldX=localFieldY=localFieldZ=0.0;
            break;
        case kInside:
            break;
    }
    G4ThreeVector localPosField(localFieldX, localFieldY, localFieldZ);
    G4ThreeVector globalPosField = global2local.Inverse().TransformAxis(localPosField);

    field[0] = globalPosField.x();
    field[1] = globalPosField.y();
    field[2] = globalPosField.z();

    return;
}

EInside Ex02SimpleSolenoidPart::GetSide(G4ThreeVector& local) const {
    return SolenoidPart->GetSolid()->Inside(local);
}

G4FieldManager*  Ex02SimpleSolenoidPart::GetGlobalFieldManager() {
    return G4TransportationManager::GetTransportationManager()->GetFieldManager();
}

