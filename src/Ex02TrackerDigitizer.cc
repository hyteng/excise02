#include "Ex02TrackDigitizer.hh"
#include "Ex02TrackDigi.hh"

#include "Ex02TrackTrackerHit.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"

#include <vector>

Ex02TrackDigitizer::Ex02TrackDigitizer(G4String name) : G4VDigitizerModule(name) {

    G4String colName = "DigitsCollection";
    collectionName.push_back(colName);

}

Ex02TrackDigitizer::~Ex02TrackDigitizer() {
}

void Ex02TrackDigitizer::Digitize() {

    DigitsCollection = new Ex02TrackDigitsCollection("Ex02TrackDigitizer","DigitsCollection");
    G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();
    
    G4int THCID = DigiMan->GetHitsCollectionID("TrackerCollection");
    Ex02TrackerHitsCollection* THC = (Ex02TrackerHitsCollection*)(DigiMan->GetHitsCollection(THCID));
    
    G4int n_hit = THC->entries();
    for (G4int i=0;i<n_hit;i++) {
        G4int NStrip = (*THC)[i]->GetNStrip();
        G4int ChamberNb = (*THC)[i]->GetChamberNb();
        G4ThreeVector Posi = (*THC)[i]->GetPos();

        Ex02TrackDigi* Digi = new Ex02TrackDigi();
        Digi->SetStripNumber(0);
        DigitsCollection->insert(Digi);
    }
    StoreDigiCollection(DigitsCollection);

    G4int DCID;
    if(DCID<0)
        DCID = DigiMan->GetDigiCollectionID("Ex02TrackDigitizer/DigitsCollection");

}
