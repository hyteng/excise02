#include "Ex02EventAction.hh"

#include "Ex02TrackerHit.hh"
#include "Ex02TrackerDigi.hh"
#include "Ex02TrackerDigitizer.hh"
#include "G4DigiManager.hh"


#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"

#include <stdlib.h>
extern std::ofstream outFile;

Ex02EventAction::Ex02EventAction() : trackerCollID(-1), drawFlag("all") {

    G4DigiManager * fDM = G4DigiManager::GetDMpointer();
    Ex02TrackerDigitizer * myDM = new Ex02TrackerDigitizer("Ex02TrackerDigitizer");
    fDM->AddNewModule(myDM);
}

Ex02EventAction::~Ex02EventAction() {

}

void Ex02EventAction::BeginOfEventAction(const G4Event* evt) {

    G4int evtNb = evt->GetEventID();
    G4cout << "Event: " << evtNb << G4endl; 
    G4SDManager * SDman = G4SDManager::GetSDMpointer();

    if(trackerCollID==-1)
        trackerCollID = SDman->GetCollectionID("trackerCollection");

}

void Ex02EventAction::EndOfEventAction(const G4Event* evt) {

    G4int event_id = evt->GetEventID();

    G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
    Ex02TrackerHitsCollection* THC = 0;
    
    G4DigiManager * fDM = G4DigiManager::GetDMpointer();
    
    if(HCE) {
        THC = (Ex02TrackerHitsCollection*)(HCE->GetHC(trackerCollID));
        if(THC) {
            int n_hit = THC->entries();
            G4cout << "Number of tracker hits in this event =  " << n_hit << G4endl;
            
        }
        Ex02TrackerDigitizer * myDM = (Ex02TrackerDigitizer*)fDM->FindDigitizerModule("Ex02TrackerDigitizer");
        myDM->SetEventNumber(event_id);
        myDM->Digitize();
        G4int myDigiCollID = fDM->GetDigiCollectionID("DigitsCollection");
        Ex02TrackerDigitsCollection *DC = (Ex02TrackerDigitsCollection*)fDM->GetDigiCollection(myDigiCollID);
        if(DC) {
            G4int n_digi = DC->entries();
            for (G4int i=0;i<n_digi;i++) {
                G4int RunNumber = (*DC)[i]->GetRun();
                outFile << std::setw(7) << RunNumber << " ";
                G4int EventNumber = (*DC)[i]->GetEvent();
                outFile << std::setw(7) << EventNumber << " ";
                G4int DetId = (*DC)[i]->GetDetector();
                outFile << std::setw(7) << DetId << " ";
                G4int NStrip = (*DC)[i]->GetStrip();
                outFile << std::setw(7) << NStrip << " ";
                G4ThreeVector DigiPos = (*DC)[i]->GetPosition();
                outFile << std::setw(7) << DigiPos.x() << " ";
                outFile << std::setw(7) << DigiPos.y() << " ";
                outFile << std::setw(7) << DigiPos.z() << " ";
                G4double Pt = (*DC)[i]->GetPt();
                outFile << std::setw(7) << Pt << " ";
                G4ThreeVector SimPos = (*DC)[i]->GetSimPosition();
                outFile << std::setw(7) << SimPos.x() << " ";
                outFile << std::setw(7) << SimPos.y() << " ";
                outFile << std::setw(7) << SimPos.z() << " ";
                outFile << "\n";
            }
        }
    }
}  


