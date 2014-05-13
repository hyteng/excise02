
#include "Ex02TrackerSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"


Ex02TrackerSD::Ex02TrackerSD(G4String name) : G4VSensitiveDetector(name) {
    G4String HCname;
    collectionName.insert(HCname="trackerCollection");
}


Ex02TrackerSD::~Ex02TrackerSD(){ 
}


void Ex02TrackerSD::Initialize(G4HCofThisEvent* HCE) {
    trackerCollection = new Ex02TrackerHitsCollection
        (SensitiveDetectorName,collectionName[0]); 
    static G4int HCID = -1;
    if(HCID<0)
    { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
    HCE->AddHitsCollection(HCID, trackerCollection); 
}


G4bool Ex02TrackerSD::ProcessHits(G4Step* aStep,G4TouchableHistory*) {
    G4double edep = aStep->GetTotalEnergyDeposit();

    if(edep != 1.*MeV) return false;

    Ex02TrackerHit* newHit = new Ex02TrackerHit();
    newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
    newHit->SetChamberNb(aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber());
    newHit->SetEdep(edep);
    newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());
    trackerCollection->insert(newHit);

    //newHit->Print();
    //newHit->Draw();

    return true;
}


void Ex02TrackerSD::EndOfEvent(G4HCofThisEvent*) {
    if (verboseLevel>0) { 
        G4int NbHits = trackerCollection->entries();
        G4cout << "\n-------->Hits Collection: in this event they are " << NbHits 
            << " hits in the tracker chambers: " << G4endl;
        for (G4int i=0;i<NbHits;i++) (*trackerCollection)[i]->Print();
    } 
}


