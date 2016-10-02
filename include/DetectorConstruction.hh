//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class G4Region;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

  DetectorConstruction();

  ~DetectorConstruction();

  G4VPhysicalVolume* Construct();

  G4Region* GetTarget1Region()  {return fRegion1;}
  G4Region* GetTarget2Region()  {return fRegion2;}
  G4Region* GetTarget3Region()  {return fRegion3;}
                         
private:
   
  G4double           fWorldSizeX;
  G4double           fWorldSizeY;
  G4double           fWorldSizeZ;
  G4double           fdist1;
  G4double           fdist2;

  G4VPhysicalVolume* fPhysiWorld;
  G4LogicalVolume*   fLogicWorld;  
  G4Box*             fSolidWorld;

  G4Material*        fNMaterial;
  G4Material*        fBeMaterial;
  G4Material*        fSiMaterial;
  G4Region*          fRegion1;
  G4Region*          fRegion2;
  G4Region*          fRegion3;

  void DefineMaterials();

  G4VPhysicalVolume* ConstructDetector();     
};
#endif
