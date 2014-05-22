/*=============================================================================
#     FileName: Ex02DetectorConstruction.hh
#         Desc: detector construction header
#       Author: Haiyun.Teng
#        Email: tenghy@ihep.ac.cn
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2013-03-23 02:38:27
#      History:
=============================================================================*/
#ifndef Ex02DetectorConstruction_h 
#define Ex02DetectorConstruction_h 1

#include "Ex02MagneticField.hh"

#include "G4VUserDetectorConstruction.hh"

#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4UserLimits;
class G4Element;

class Ex02DetectorConstruction : public G4VUserDetectorConstruction {
    public:
        Ex02DetectorConstruction();
        ~Ex02DetectorConstruction();

    public:
        G4VPhysicalVolume* Construct();

    private:
        void SetMagField(G4double);

        G4LogicalVolume* experimentalHall_log;
        G4LogicalVolume* trackerBlock_log;
        G4LogicalVolume* trackerLayer_log;
        G4VPhysicalVolume* experimentalHall_phys;
        G4VPhysicalVolume* trackerBlock_phys;
        G4VPhysicalVolume* trackerLayer_phys;

        G4UserLimits* fStepLimit;

        Ex02MagneticField* fpMagField;

        G4Element* H;
        G4Element* O;
        G4Element* C;
        G4Element* N;
};

#endif
