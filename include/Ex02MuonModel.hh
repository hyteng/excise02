/*=============================================================================
#     FileName: Ex02Ex02MuonModel.hh
#         Desc: detector physics listn header
#       Author: Haiyun.Teng
#        Email: tenghy@ihep.ac.cn
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2013-05-05 02:38:27
#      History:
=============================================================================*/
#ifndef Ex02MuonModel_h
#define Ex02MuonModel_h

#include "G4VFastSimulationModel.hh"
#include "G4Step.hh"
#include "G4TouchableHandle.hh"


class Ex02MuonModel : public G4VFastSimulationModel {

    public:
        Ex02MuonModel(G4String, G4Region*);
        Ex02MuonModel(G4String);
        ~Ex02MuonModel();

        // -- IsApplicable
        G4bool IsApplicable(const G4ParticleDefinition&);
        // -- ModelTrigger 
        G4bool ModelTrigger(const G4FastTrack &);
        // -- User method DoIt 
        void DoIt(const G4FastTrack&, G4FastStep&); 

    private:
        G4Step  *fFakeStep;
        G4TouchableHandle   fTouchableHandle;
        G4Navigator *fpNavigator;
        G4bool  fNaviSetup;
};

#endif
