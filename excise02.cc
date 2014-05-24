/*=============================================================================
#     FileName: excise01.cc
#         Desc: geant4 detector simulation excise01
#       Author: Haiyun.Teng
#        Email: tenghy@ihep.ac.cn
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2013-03-22 15:15:10
#      History: 
=============================================================================*/

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "Ex02DetectorConstruction.hh"
#include "Ex02PhysicsList.hh"
//#include "G4VModularPhysicsList.hh"
#include "QGSP_BERT.hh"
#include "Ex02PrimaryGeneratorAction.hh"
#include "Ex02RunAction.hh"
#include "Ex02EventAction.hh"
//#include "Ex02StackingAction.hh"
//#include "Ex02TrackingAction.hh"
#include "Ex02SteppingAction.hh"
#include "Ex02SteppingVerbose.hh"

#include "G4StepLimiterPhysics.hh"

//#include "G4GlobalFastSimulationManager.hh"

#define G4VIS_USE 0

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#define G4STORE_DATA 1

std::ofstream outFile;

int main(int argc, char** argv) {

    // Seed the random number generator
    G4long mySeed = 123456;
    CLHEP::HepRandom::setTheSeed(mySeed);

    std::string FileName = "rundata.txt";
    #ifdef G4STORE_DATA
    outFile.open(FileName.c_str());
    #endif


    // User Verbose output class
    G4VSteppingVerbose* verbosity = new Ex02SteppingVerbose;
    G4VSteppingVerbose::SetInstance(verbosity);

    // Run manager
    G4RunManager* theRunManager = new G4RunManager;

    // UserInitialization class - mandatory
    //G4VUserDetectorConstruction* theDetector = new Ex02DetectorConstruction;
    Ex02DetectorConstruction* theDetector = new Ex02DetectorConstruction;
    theDetector->SetROStripNumber(20);
    theRunManager->SetUserInitialization(theDetector);

    //G4VUserPhysicsList* thePhysicsList = new QGSP_BERT();
    G4VUserPhysicsList* thePhysicsList = new Ex02PhysicsList;
    //thePhysicsList->RegisterPhysics(new G4StepLimiterPhysics());
    theRunManager->SetUserInitialization(thePhysicsList);

    G4VUserPrimaryGeneratorAction* theGenAction = new Ex02PrimaryGeneratorAction;
    theRunManager->SetUserAction(theGenAction);
    
    // User Action
    
    G4UserRunAction* theRunAction = new Ex02RunAction;
    theRunManager->SetUserAction(theRunAction);

    G4UserEventAction* theEventAction = new Ex02EventAction;
    theRunManager->SetUserAction(theEventAction);

    //G4UserStackingAction* theStackingAction = new Ex02StackingAction;
    //theRunManager->SetUserAction(theStackingAction);

    //G4UserTrackingAction* theTrackingAction = new Ex02TrackingAction;
    //theRunManager->SetUserAction(theTrackingAction);

    G4UserSteppingAction* theSteppingAction = new Ex02SteppingAction;
    theRunManager->SetUserAction(theSteppingAction);

    theRunManager->Initialize();

    #ifdef G4VIS_USE
    G4VisManager* theVisManager = new G4VisExecutive;
    theVisManager->Initialize();
    #endif

    //G4int EventNumber = 10;
    //theRunManager->BeamOn(EventNumber);

    // User Interface
    G4UImanager* theUIManager = G4UImanager::GetUIpointer();

    if(argc != 1) {
        G4String theCommand = "/control/execute ";
        G4String theFileName = argv[1];
        theUIManager->ApplyCommand(theCommand+theFileName);
    }
    else {
        #ifdef G4UI_USE
            G4UIExecutive *theUI = new G4UIExecutive(argc, argv);
            #ifdef G4VIS_USE
                theUIManager->ApplyCommand("/control/execute init_vis.mac");
            #else
                theUImanager->ApplyCommand("/control/execute init.mac");
            #endif
            theUI->SessionStart();
            delete theUI;
        #endif
    }

    #ifdef G4STORE_DATA
    outFile.close();
    #endif

    #ifdef G4VIS_USE
    delete theVisManager;   
    #endif 

    //Job termination
    delete verbosity;
    delete theRunManager;

    return 0;
}

