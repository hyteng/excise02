/*=============================================================================
#     FileName: Ex02PhysicsList.hh
#         Desc: detector physics listn header
#       Author: Haiyun.Teng
#        Email: tenghy@ihep.ac.cn
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2013-04-23 02:38:27
#      History:
=============================================================================*/
#ifndef Ex02PhysicsList_h 
#define Ex02PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class Ex02PhysicsList: public G4VUserPhysicsList {

    public:
        Ex02PhysicsList();
        ~Ex02PhysicsList();

    protected:
        void ConstructParticle();
        void ConstructProcess();
        void SetCuts(); 

    private:
        void ConstructLeptons();
        void ConstructBosons();

        void ConstructEM();

        void AddParameterisation();
};

#endif
