#include "Ex02MuonModel.hh"

#include "G4TouchableHandle.hh"
#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"
#include "G4SystemOfUnits.hh"


Ex02MuonModel::Ex02MuonModel(G4String modelName, G4Region* envelope) : G4VFastSimulationModel(modelName, envelope) {
}

Ex02MuonModel::Ex02MuonModel(G4String modelName) : G4VFastSimulationModel(modelName) {
}

Ex02MuonModel::~Ex02MuonModel() {
}

bool Ex02MuonModel::IsApplicable(const G4ParticleDefinition& particleType) {
    return &particleType == G4MuonMinus::MuonMinusDefinition() || &particleType == G4MuonPlus::MuonPlusDefinition();
}

bool Ex02MuonModel::ModelTrigger(const G4FastTrack& fastTrack) {
    return fastTrack.GetPrimaryTrack()->GetKineticEnergy() > 1*MeV;
}

void Ex02MuonModel::DoIt(const G4FastTrack& fastTrack, G4FastStep& fastStep) {

    G4String DetectorName = fastTrack.GetEnvelopePhysicalVolume()->GetName();
    int DetectotCopyNumber = fastTrack.GetEnvelopePhysicalVolume()->GetCopyNo();
    G4TouchableHandle Touch0 = fastTrack.GetPrimaryTrack()->GetTouchableHandle();
    G4StepPoint* Point0 = fastTrack.GetPrimaryTrack()->GetStep()->GetPreStepPoint();
    if(DetectorName== "Tracker" && Point0->GetStepStatus() == fGeomBoundary) {
        fastStep.ProposeTotalEnergyDeposited(1.*MeV);
    }
    double distance = fastTrack.GetEnvelopeSolid()->DistanceToOut(fastTrack.GetPrimaryTrackLocalPosition(), fastTrack.GetPrimaryTrackLocalDirection());
    G4ThreeVector position = fastTrack.GetPrimaryTrackLocalPosition() + distance*fastTrack.GetPrimaryTrackLocalDirection();
    fastStep.ProposePrimaryTrackFinalPosition(position);
}
