#include "Ex02PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"


Ex02PrimaryGeneratorAction::Ex02PrimaryGeneratorAction() {

  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
  particleGun->SetParticleEnergy(100.0*GeV);
  particleGun->SetParticlePosition(G4ThreeVector(-2.5*m, 0.0, 0.0));
}

Ex02PrimaryGeneratorAction::~Ex02PrimaryGeneratorAction() {
  delete particleGun;
}

void Ex02PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

  G4int i = anEvent->GetEventID() % 3;
  G4ThreeVector v(1.0,0.0,0.0);
  /*
  switch(i) {
    case 0:
      break;
    case 1:
      v.setY(0.1);
      break;
    case 2:
      v.setZ(0.1);
      break;
  }
  */
  particleGun->SetParticleMomentumDirection(v);
  particleGun->GeneratePrimaryVertex(anEvent);
}


