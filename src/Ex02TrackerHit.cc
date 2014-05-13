
#include "Ex02TrackerHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<Ex02TrackerHit> Ex02TrackerHitAllocator;


Ex02TrackerHit::Ex02TrackerHit() {}


Ex02TrackerHit::~Ex02TrackerHit() {}


Ex02TrackerHit::Ex02TrackerHit(const Ex02TrackerHit& right) : G4VHit() {
    trackID   = right.trackID;
    chamberNb = right.chamberNb;
    edep      = right.edep;
    pos       = right.pos;
}


const Ex02TrackerHit& Ex02TrackerHit::operator=(const Ex02TrackerHit& right) {
    trackID   = right.trackID;
    chamberNb = right.chamberNb;
    edep      = right.edep;
    pos       = right.pos;
    return *this;
}


G4int Ex02TrackerHit::operator==(const Ex02TrackerHit& right) const {
    return (this==&right) ? 1 : 0;
}


void Ex02TrackerHit::Draw() {

    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if(pVVisManager)
    {
        G4Circle circle(pos);
        circle.SetScreenSize(2.);
        circle.SetFillStyle(G4Circle::filled);
        G4Colour colour(1.,0.,0.);
        G4VisAttributes attribs(colour);
        circle.SetVisAttributes(attribs);
        pVVisManager->Draw(circle);
    }
}


void Ex02TrackerHit::Print() {

    G4cout << "  trackID: " << trackID << "  chamberNb: " << chamberNb
        << "  energy deposit: " << G4BestUnit(edep,"Energy")
        << "  position: " << G4BestUnit(pos,"Length") << G4endl;
}


