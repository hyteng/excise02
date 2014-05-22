#include "Ex02TrackerDigi.hh"

G4Allocator<Ex02TrackerDigi> Ex02TrackerDigiAllocator;

Ex02TrackerDigi::Ex02TrackerDigi() {
    RunNumber = -1;
    EventNumber = -1;
    DetectorNumber = 0;
    StripNumber = -1;
    GlobalPosition = G4ThreeVector(0., 0., 0.);
    GlobalError = G4ThreeVector(0., 0., 0.);
    GlobalSimPosition = G4ThreeVector(0., 0., 0.);
    Pt = 0.;
}

Ex02TrackerDigi::Ex02TrackerDigi(const Ex02TrackerDigi& right) : G4VDigi() {
    RunNumber = right.RunNumber;
    EventNumber = right.EventNumber;
    DetectorNumber = right.DetectorNumber;
    StripNumber = right.StripNumber;
    GlobalPosition = right.GlobalPosition;
    GlobalError = right.GlobalError;
    GlobalSimPosition = right.GlobalSimPosition;
    Pt = right.Pt;
}

Ex02TrackerDigi::~Ex02TrackerDigi() {
}

const Ex02TrackerDigi& Ex02TrackerDigi::operator=(const Ex02TrackerDigi& right) {
    RunNumber = right.RunNumber;
    EventNumber = right.EventNumber;
    DetectorNumber = right.DetectorNumber;
    StripNumber = right.StripNumber;
    GlobalPosition = right.GlobalPosition;
    GlobalError = right.GlobalError;
    GlobalSimPosition = right.GlobalSimPosition;
    Pt = right.Pt;

    return *this;
}

int Ex02TrackerDigi::operator==(const Ex02TrackerDigi& right) const {
    return ((RunNumber==right.RunNumber)&&(EventNumber==right.EventNumber)&&(DetectorNumber==right.DetectorNumber)&&(StripNumber==right.StripNumber)&&(GlobalPosition==right.GlobalPosition)&&(GlobalError==right.GlobalError)&&(GlobalSimPosition==right.GlobalSimPosition)&&(Pt==right.Pt));
}

void Ex02TrackerDigi::Draw() {
}

void Ex02TrackerDigi::Print() {
}
