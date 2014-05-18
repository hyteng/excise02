#ifndef Ex02RunAction_h
#define Ex02RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class Ex02RunAction : public G4UserRunAction
{
public:
  Ex02RunAction();
  ~Ex02RunAction();
  
public:
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

private:
};

#endif


