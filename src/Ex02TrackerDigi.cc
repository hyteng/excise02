#include "Ex02TrackerDigi.hh"

G4Allocator<Ex02TrackerDigi> Ex02TrackerDigiAllocator;

Ex02TrackerDigi::Ex02TrackerDigi() {
    DetectorNumber = 0;
    StripNumber=0;
    GlobalPosition = G4ThreeVector(0., 0., 0.);
    GlobalError = G4ThreeVector(0., 0., 0.);
    GlobalSimPosition = G4ThreeVector(0., 0., 0.);
}

Ex02TrackerDigi::Ex02TrackerDigi(const Ex02TrackerDigi& right) : G4VDigi() {
    DetectorNumber = right.DetectorNumber;
    StripNumber = right.StripNumber;
    GlobalPosition = right.GlobalPosition;
    GlobalError = right.GlobalError;
    GlobalSimPosition = right.GlobalSimPosition;
}

Ex02TrackerDigi::~Ex02TrackerDigi() {
}

const Ex02TrackerDigi& Ex02TrackerDigi::operator=(const Ex02TrackerDigi& right) {

    DetectorNumber = right.DetectorNumber;
    StripNumber = right.StripNumber;
    GlobalPosition = right.GlobalPosition;
    GlobalError = right.GlobalError;
    GlobalSimPosition = right.GlobalSimPosition;

    return *this;
}

int Ex02TrackerDigi::operator==(const Ex02TrackerDigi& right) const {
    return ((DetectorNumber==right.DetectorNumber)&&(StripNumber==right.StripNumber)&&(GlobalPosition==right.GlobalPosition)&&(GlobalError==right.GlobalError)&&(GlobalSimPosition==right.GlobalSimPosition));
}

void Ex02TrackerDigi::Draw() {
}

void Ex02TrackerDigi::Print() {
}
