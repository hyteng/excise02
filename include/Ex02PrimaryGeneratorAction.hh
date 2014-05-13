/*=============================================================================
#     FileName: Ex02PhysicsList.h
#         Desc: detector physics listn header
#       Author: Haiyun.Teng
#        Email: tenghy@ihep.ac.cn
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2013-04-23 02:38:27
#      History:
=============================================================================*/

#ifndef Ex02PrimaryGeneratorAction_h
#define Ex02PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class Ex02PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  public:
    Ex02PrimaryGeneratorAction();
    ~Ex02PrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* anEvent);

  private:
    G4ParticleGun* particleGun;
};

#endif


