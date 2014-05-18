#ifndef Ex02EventAction_h
#define Ex02EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class G4Event;

class Ex02EventAction : public G4UserEventAction
{
  public:
    Ex02EventAction();
   ~Ex02EventAction();

  public:
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);

    void SetDrawFlag(G4String val) {drawFlag = val;};

  private:
    G4int       trackerCollID; 
    G4String    drawFlag;

};

#endif


