#ifndef Ex02SteppingAction_h
#define Ex02SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class Ex02SteppingAction : public G4UserSteppingAction
{
  public:
    Ex02SteppingAction();
    virtual ~Ex02SteppingAction(){};

    virtual void UserSteppingAction(const G4Step*);

  private:
    G4bool drawFlag;

  public:
    inline void SetDrawFlag(G4bool val) { drawFlag = val; };
};

#endif
