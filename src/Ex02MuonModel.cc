#include "Ex02MuonModel.hh"

#include "G4TouchableHandle.hh"
#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4TransportationManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"


Ex02MuonModel::Ex02MuonModel(G4String modelName, G4Region* envelope) : G4VFastSimulationModel(modelName, envelope) {
    fFakeStep          = new G4Step();
    fTouchableHandle   = new G4TouchableHistory();
    fpNavigator        = new G4Navigator();
    fNaviSetup         = false;
}

Ex02MuonModel::Ex02MuonModel(G4String modelName) : G4VFastSimulationModel(modelName) {
    fFakeStep          = new G4Step();
    fTouchableHandle   = new G4TouchableHistory();
    fpNavigator        = new G4Navigator();
    fNaviSetup         = false;
}

Ex02MuonModel::~Ex02MuonModel() {
}

bool Ex02MuonModel::IsApplicable(const G4ParticleDefinition& particleType) {
    bool isApp = false;
    if(&particleType == G4MuonMinus::MuonMinusDefinition() || &particleType == G4MuonPlus::MuonPlusDefinition() || &particleType == G4Electron::ElectronDefinition() || &particleType == G4Positron::PositronDefinition())
        isApp = true;
    G4cout << "IsApplicable: " << isApp << G4endl;
    return isApp;
}

bool Ex02MuonModel::ModelTrigger(const G4FastTrack& fastTrack) {
    bool isTrigger = false;
    if(fastTrack.GetPrimaryTrack()->GetKineticEnergy() >= 1*MeV)
        isTrigger = true;

    G4cout << "isTrigger: " << isTrigger << G4endl;
    return isTrigger;
}

void Ex02MuonModel::DoIt(const G4FastTrack& fastTrack, G4FastStep& fastStep) {

    G4cout << "Parameterisatin DoIt:" << G4endl;
    G4String DetectorName = fastTrack.GetEnvelopePhysicalVolume()->GetName();
    int DetectotCopyNumber = fastTrack.GetEnvelopePhysicalVolume()->GetCopyNo();
    G4TouchableHandle Touch0 = fastTrack.GetPrimaryTrack()->GetTouchableHandle();
    G4cout << "DetectorName: " << DetectorName << ", DetectotCopyNumber: " << DetectotCopyNumber << G4endl;

    G4StepPoint* globalPoint0 = fastTrack.GetPrimaryTrack()->GetStep()->GetPreStepPoint();
    G4ThreeVector globalPos0 = fastTrack.GetPrimaryTrack()->GetPosition();
    G4ThreeVector localPos0 = fastTrack.GetPrimaryTrackLocalPosition();
    G4cout << "PreStep: " << globalPoint0->GetPosition() << ". PrimaryTrack: globalPos0: " << globalPos0 << ", localPos0: " << localPos0 << G4endl;

    if(DetectorName== "trackerLayer" && globalPoint0->GetStepStatus() == fGeomBoundary) {
        fastStep.ProposeTotalEnergyDeposited(1.*MeV);
        G4cout << "EnergyDeposited 1Mev" << G4endl;
    }

    double distance = fastTrack.GetEnvelopeSolid()->DistanceToOut(localPos0, fastTrack.GetPrimaryTrackLocalDirection());
    G4ThreeVector localPos1 = localPos0 + distance*fastTrack.GetPrimaryTrackLocalDirection();
    G4ThreeVector localPos2 = localPos0 + distance*0.2*fastTrack.GetPrimaryTrackLocalDirection();
    G4ThreeVector globalPos1 = globalPos0 + distance*fastTrack.GetPrimaryTrack()->GetMomentumDirection();
    G4ThreeVector globalPos2 = globalPos0 + distance*0.2*fastTrack.GetPrimaryTrack()->GetMomentumDirection();
    G4cout << "DistanceToOut: " << distance << ". localPos1: " << localPos1 << ". localPos2: " << localPos2 << ". globalPos1: " << globalPos1 << ". globalPos2: " << globalPos2 << G4endl;

    fastStep.ProposePrimaryTrackFinalPosition(localPos1);
    fastStep.ProposePrimaryTrackPathLength(distance);
    
    if(!fNaviSetup) {
        fpNavigator->SetWorldVolume(G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking()->GetWorldVolume());
        fpNavigator->LocateGlobalPointAndUpdateTouchableHandle(globalPos2, G4ThreeVector(0.,0.,0.), fTouchableHandle, false);
        fNaviSetup = true;
    }
    else {
        fpNavigator->LocateGlobalPointAndUpdateTouchableHandle(globalPos2, G4ThreeVector(0.,0.,0.), fTouchableHandle);
    }
    //fFakeStep->SetPreStepPoint(globalPoint0);
    //fFakeStep->GetPostStepPoint()->SetPosition(globalPos1);
    fFakeStep->GetPreStepPoint()->SetTouchableHandle(fTouchableHandle);
    fFakeStep->SetTotalEnergyDeposit(1.*MeV);

    G4VPhysicalVolume* pCurrentVolume = fFakeStep->GetPreStepPoint()->GetPhysicalVolume();
    G4cout << "FakeStep in PV: " << pCurrentVolume->GetName() << G4endl;
    G4VSensitiveDetector* pSensitive;
    if(pCurrentVolume != 0) {
        pSensitive = pCurrentVolume->GetLogicalVolume()->GetSensitiveDetector();
        G4cout << "FakeStep in SD: " << pSensitive->GetName() << G4endl;
        if(pSensitive != 0)
            pSensitive->Hit(fFakeStep);
    }
   
}
