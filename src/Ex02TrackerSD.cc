
#include "Ex02TrackerSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"

Ex02TrackerSD::Ex02TrackerSD(G4String name) : G4VSensitiveDetector(name) {
    G4String HCname;
    collectionName.insert(HCname="trackerCollection");
}


Ex02TrackerSD::~Ex02TrackerSD() { 
}


void Ex02TrackerSD::Initialize(G4HCofThisEvent* HCE) {
    trackerCollection = new Ex02TrackerHitsCollection(SensitiveDetectorName, collectionName[0]); 
    static G4int HCID = -1;
    if(HCID<0) { 
        HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); 
    }
    HCE->AddHitsCollection(HCID, trackerCollection);

    G4cout << "SD Initialize: " << HCID << G4endl;
    for(int i=0;i<5;i++)
        for(int j=0;j<40;j++)
            tracker[i][j] = -1;
}


G4bool Ex02TrackerSD::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist) {

    G4double edep = aStep->GetTotalEnergyDeposit();
    G4cout << "edep: " << edep << G4endl;
    if(edep < 0.1*MeV) 
        edep = 1.0*MeV;
    //return false;

    G4VPhysicalVolume* ROPV = ROhist->GetVolume();
    G4String ROPVName = ROPV->GetName();
    G4int ROPVNumber = ROPV->GetCopyNo();
    G4cout << "ROVolumeName: " << ROPVName << ", CopyNo: " << ROPVNumber << G4endl;
    if(ROPVName == "trackerLayer") {
        G4ThreeVector GlobalHitPosition = aStep->GetPreStepPoint()->GetPosition();
        G4ThreeVector LocalHitPosition = ROhist->GetHistory()->GetTopTransform().TransformPoint(GlobalHitPosition);
        G4LogicalVolume* TrakerLayerLV = ROPV->GetLogicalVolume();
        G4int stripPVNumber = -1;
        double residual_tmp = 100.0*cm;
        for(G4int i=0; i < TrakerLayerLV->GetNoDaughters(); i++) {
            G4VPhysicalVolume* StripPV = TrakerLayerLV->GetDaughter(i);
            G4int stripPVN = StripPV->GetCopyNo();
            G4ThreeVector stripLocalPos = StripPV->GetTranslation();
            if((stripLocalPos-LocalHitPosition).z() < residual_tmp) {
                stripPVNumber = stripPVN;
                residual_tmp = (stripLocalPos-LocalHitPosition).z();
            }
        }

        if(stripPVNumber != -1) {
            if(tracker[ROPVNumber][stripPVNumber] == -1) {
                Ex02TrackerHit* newHit = new Ex02TrackerHit();
                newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
                newHit->SetChamberNb(ROPVNumber);
                newHit->SetStrip(stripPVNumber);
                newHit->SetEdep(edep);
                newHit->SetHitPos(GlobalHitPosition);
                G4ThreeVector StripLocalPosition = TrakerLayerLV->GetDaughter(stripPVNumber)->GetTranslation();
                G4ThreeVector GlobalDigiPosition = ROhist->GetHistory()->GetTopTransform().Inverse().TransformPoint(StripLocalPosition);
                newHit->SetDigiPos(GlobalDigiPosition);
                G4Box *trackerLayer_box = (G4Box*)(TrakerLayerLV->GetDaughter(stripPVNumber)->GetLogicalVolume()->GetSolid());
                G4ThreeVector localError(trackerLayer_box->GetXHalfLength(), trackerLayer_box->GetYHalfLength(), trackerLayer_box->GetZHalfLength());
                G4ThreeVector globalError = ROhist->GetHistory()->GetTopTransform().Inverse().TransformPoint(localError);
                newHit->SetError(localError);

                G4ThreeVector P = aStep->GetTrack()->GetMomentum();
                newHit->SetPt(P.mag());
                tracker[ROPVNumber][stripPVNumber] = trackerCollection->insert(newHit) - 1;
                G4cout << "stripPVNumber: " << stripPVNumber << ", StripLocalPosition: " << StripLocalPosition << ", GlobalDigiPosition: " << GlobalDigiPosition << ", localError: " << localError << G4endl;
            }
            else
                (*trackerCollection)[tracker[ROPVNumber][stripPVNumber]]->AddEdep(edep);
            return true;
        }
    }
    return false;
}


void Ex02TrackerSD::EndOfEvent(G4HCofThisEvent* HCE) {
    if (verboseLevel>0) { 
        G4int NbHits = trackerCollection->entries();
        G4cout << "\n-------->Hits Collection: in this event they are " << NbHits 
            << " hits in the tracker chambers: " << G4endl;
        for (G4int i=0;i<NbHits;i++) (*trackerCollection)[i]->Print();
    }
    static G4int HCID = -1;
    if(HCID<0)
        HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    HCE->AddHitsCollection(HCID, trackerCollection); 

    for(int i=0;i<5;i++)
        for(int j=0;j<40;j++)
            tracker[i][j] = -1;

}


