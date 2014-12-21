#include "Ex02RunAction.hh"
#include "Ex02TrackerDigitizer.hh"

#include <stdlib.h>
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"

#include <stdlib.h>
#include <fstream>

extern std::ofstream outFile;

Ex02RunAction::Ex02RunAction() {
}

Ex02RunAction::~Ex02RunAction() {
}

void Ex02RunAction::BeginOfRunAction(const G4Run* aRun) {  

    G4DigiManager * fDM = G4DigiManager::GetDMpointer();
    Ex02TrackerDigitizer * myDM = (Ex02TrackerDigitizer*)fDM->FindDigitizerModule("Ex02TrackerDigitizer");
    myDM->SetRunNumber(aRun->GetRunID());
  //char name[15];
  //sprintf(name,"Tracks_%d.dat", aRun->GetRunID());

//#ifdef G4STORE_DATA
//  outFile.open(name);
//#endif

  // Prepare the visualization
  if(G4VVisManager::GetConcreteInstance()) {
      G4UImanager* UI = G4UImanager::GetUIpointer(); 
      UI->ApplyCommand("/vis/scene/notifyHandlers");
    } 
}

void Ex02RunAction::EndOfRunAction(const G4Run* aRun) {

//  char name[15];
//  sprintf(name,"Tracks_%d.dat", aRun->GetRunID());
  G4cout << "End of Run " << G4endl;
//  G4cout << "File " << name << G4endl;

  // Run ended, update the visualization
  if (G4VVisManager::GetConcreteInstance()) {
     G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
  }

  // Close the file with the hits information
//#ifdef G4STORE_DATA
//  outFile.close();
//#endif

}


