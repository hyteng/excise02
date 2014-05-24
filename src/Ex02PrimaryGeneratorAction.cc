#include "Ex02PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "Randomize.hh"

Ex02PrimaryGeneratorAction::Ex02PrimaryGeneratorAction() {

    G4int n_particle = 1;
    particleGun = new G4ParticleGun(n_particle);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="mu-"));
    //particleGun->SetParticleEnergy(100.0*GeV);
    particleGun->SetParticlePosition(G4ThreeVector(-0.0*m, 0.0, 0.0));
}

Ex02PrimaryGeneratorAction::~Ex02PrimaryGeneratorAction() {
    delete particleGun;
}

void Ex02PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

    G4int i = anEvent->GetEventID()%5;
    G4ThreeVector v0(1.0,0.0,0.0);
    double angle = CLHEP::RandFlat::shoot(-0.25, 0.25);
    angle = 0.25;
    G4ThreeVector v = v0.rotateY(angle);
    G4cout << "angle: " << angle << ", v: " << v << G4endl;
    double P;
    switch(i) {
        case 0:
            P = 10.0;
        case 1:
            P = 20.0;
            break;
        case 2:
            P = 30.0;
            break;
        case 3:
            P = 40.0;
        case 4:
            P = 50.0;
    }
    //P = 50.0;
    particleGun->SetParticleEnergy(P*GeV);
    particleGun->SetParticleMomentumDirection(v);
    particleGun->GeneratePrimaryVertex(anEvent);
}
