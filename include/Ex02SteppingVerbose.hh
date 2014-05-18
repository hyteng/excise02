#ifndef Ex02SteppingVerbose_h
#define Ex02SteppingVerbose_h 1

#include "G4SteppingVerbose.hh"

class Ex02SteppingVerbose : public G4SteppingVerbose {
 public:
   
  Ex02SteppingVerbose();
 ~Ex02SteppingVerbose();

  void StepInfo();
  void TrackingStarted();

};


#endif
