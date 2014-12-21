#include "Ex02TrackerDigitizer.hh"
#include "Ex02TrackerDigi.hh"
#include "Ex02TrackerHit.hh"

#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

#include <vector>

Ex02TrackerDigitizer::Ex02TrackerDigitizer(G4String name) : G4VDigitizerModule(name) {

    G4String colName = "DigitsCollection";
    collectionName.push_back(colName);

}

Ex02TrackerDigitizer::~Ex02TrackerDigitizer() {
}

void Ex02TrackerDigitizer::Digitize() {

    DigitsCollection = new Ex02TrackerDigitsCollection("Ex02TrackerDigitizer","DigitsCollection");
    G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();
    
    G4int THCID = DigiMan->GetHitsCollectionID("trackerCollection");
    Ex02TrackerHitsCollection* THC = (Ex02TrackerHitsCollection*)(DigiMan->GetHitsCollection(THCID));
    
    G4int n_hit = THC->entries();
    for(G4int i=0;i<n_hit;i++) {
        G4int TrackerId = (*THC)[i]->GetTrackID();
        G4int StripNb = (*THC)[i]->GetStrip();
        G4int ChamberNb = (*THC)[i]->GetChamberNb();
        G4ThreeVector simPos = (*THC)[i]->GetHitPos();
        G4ThreeVector Pos = (*THC)[i]->GetDigiPos();
        G4ThreeVector error = (*THC)[i]->GetError();
        G4double pt = (*THC)[i]->GetPt();
        
        Ex02TrackerDigi* Digi = new Ex02TrackerDigi();
        Digi->SetRun(RunNumber);
        Digi->SetEvent(EventNumber);
        Digi->SetDetector(ChamberNb);
        Digi->SetStrip(StripNb);
        Digi->SetPosition(Pos);
        Digi->SetSimPosition(simPos);
        Digi->SetError(error);
        Digi->SetPt(pt);

        DigitsCollection->insert(Digi);
    }
    StoreDigiCollection(DigitsCollection);

    G4int DCID=-1;
    if(DCID<0)
        DCID = DigiMan->GetDigiCollectionID("Ex02TrackerDigitizer/DigitsCollection");

}
