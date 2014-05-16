#include "Ex02TrackDigi.hh"

G4Allocator<Ex02TrackDigi> Ex02TrackDigiAllocator;

Ex02TrackDigi::Ex02TrackDigi() {
    DetectorNumber = 0;
    StripNumber=0;
    GlobalPosition(0., 0., 0.);
    GlobalError(0., 0., 0.);
}

Ex02TrackDigi::Ex02TrackDigi(const Ex02TrackDigi& right) : G4VDigi() {
    DetectorNumber = right.DetectorNumber;
    StripNumber = right.StripNumber;
    GlobalPosition = right.GlobalPosition;
    GlobalError = right.GlobalError;
}

Ex02TrackDigi::~Ex02TrackDigi() {
}

const Ex02TrackDigi& Ex02TrackDigi::operator=(const Ex02TrackDigi& right) {

    DetectorNumber = right.DetectorNumber;
    StripNumber = right.StripNumber;
    GlobalPosition = right.GlobalPosition;
    GlobalError = right.GlobalError;

    return *this;
}

int Ex02TrackDigi::operator==(const Ex02TrackDigi& right) const {
    return ((DetectorNumber==right.DetectorNumber)&&(StripNumber==right.StripNumber)&&(GlobalPosition==right.GlobalPosition)&&(GlobalError==right.GlobalError));
}

void Ex02TrackDigi::Draw() {
}

void Ex02TrackDigi::Print() {
}
