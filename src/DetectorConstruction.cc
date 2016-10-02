#include "DetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

DetectorConstruction::DetectorConstruction()
:fPhysiWorld(NULL), fLogicWorld(NULL), fSolidWorld(NULL)
{}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

DetectorConstruction::~DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VPhysicalVolume* DetectorConstruction::Construct()

{
  DefineMaterials();
  return ConstructDetector();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void DetectorConstruction::DefineMaterials()
{ 

  // Nitrogen and silicon are defined from NIST material database
  G4NistManager * man = G4NistManager::Instance();
  G4Material * N = man->FindOrBuildMaterial("G4_N");
  G4Material * Be = man->FindOrBuildMaterial("G4_Be");
  G4Material * Si = man->FindOrBuildMaterial("G4_Si");

  // Default materials in setup.
  fNMaterial = N;
  fBeMaterial = Be;
  fSiMaterial = Si;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
G4VPhysicalVolume* DetectorConstruction::ConstructDetector()
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

  // WORLD VOLUME
  
  fWorldSizeX  = 2.2*cm; 
  fWorldSizeY  = 2.2*cm; 
  fWorldSizeZ  = 2.2*cm;
  fdist1 = 5*mm;
  fdist2 = 2*mm;

  fSolidWorld = new G4Box("World",				     //its name
			   fWorldSizeX/2,fWorldSizeY/2,fWorldSizeZ/2);  //its size
  

  fLogicWorld = new G4LogicalVolume(fSolidWorld,	//its solid
				   fNMaterial,		//its material
				   "World");		//its name
  
  fPhysiWorld = new G4PVPlacement(0,			//no rotation
  				 G4ThreeVector(),	//at (0,0,0)
                                 "World",		//its name
                                 fLogicWorld,		//its logical volume
                                 0,			//its mother  volume
                                 false,			//no boolean operation
                                 0);			//copy number

  // Be Sheet (Target1)

  G4double Target1SizeZ =  25*um; 

  G4Box* target1Solid = new G4Box("Target1",				     //its name
				 fWorldSizeX/2.2,fWorldSizeY/2.2,Target1SizeZ/2);   //its size
  

  G4LogicalVolume* logicTarget1 = new G4LogicalVolume(target1Solid,       //its solid
						     fBeMaterial,	//its material
						     "Target1");		//its name

  G4double pos_x1 =  0.0*cm;
  G4double pos_y1 =  0.0*cm;
  G4double pos_z1 =  Target1SizeZ/2;
  
  new G4PVPlacement(0,			                               //no rotation
		    G4ThreeVector(pos_x1, pos_y1, pos_z1),	       //at (pos_x1, pos_y1, pos_z1)
		    "Target1",		//its name
		    logicTarget1,	//its logical volume
		    fPhysiWorld,		//its mother  volume
		    false,		//no boolean operation
		    0);			//copy number


  // Si Detector 1 (Target2)

  G4double Target2SizeZ =  320*um; 

  G4Box* target2Solid = new G4Box("Target2",				     //its name
				 fWorldSizeX/2.2,fWorldSizeY/2.2,Target2SizeZ/2);   //its size
  

  G4LogicalVolume* logicTarget2 = new G4LogicalVolume(target2Solid,       //its solid
						     fSiMaterial,	//its material
						     "Target2");		//its name
  
  G4double pos_x2 =  0.0*cm;
  G4double pos_y2 =  0.0*cm;
  G4double pos_z2 =  Target1SizeZ + fdist1 + Target2SizeZ/2;
  
  new G4PVPlacement(0,			                               //no rotation
		    G4ThreeVector(pos_x2, pos_y2, pos_z2),	       //at (pos_x2, pos_y2, pos_z2)
		    "Target2",		//its name
		    logicTarget2,	//its logical volume
		    fPhysiWorld,		//its mother  volume
		    false,		//no boolean operation
		    0);			//copy number

  // Si Detector 2 (Target3)

  G4double Target3SizeZ =  320*um; 

  G4Box* target3Solid = new G4Box("Target3",				     //its name
				 fWorldSizeX/2.2,fWorldSizeY/2.2,Target3SizeZ/2);   //its size
  

  G4LogicalVolume* logicTarget3 = new G4LogicalVolume(target3Solid,       //its solid
						     fSiMaterial,	//its material
						     "Target3");		//its name
  
  G4double pos_x3 =  0.0*cm;
  G4double pos_y3 =  0.0*cm;
  G4double pos_z3 =  Target1SizeZ + fdist1 + Target2SizeZ + fdist2 + Target3SizeZ/2;
  
  new G4PVPlacement(0,			                               //no rotation
		    G4ThreeVector(pos_x3, pos_y3, pos_z3),	       //at (pos_x3, pos_y3, pos_z3)
		    "Target3",		//its name
		    logicTarget3,	//its logical volume
		    fPhysiWorld,		//its mother  volume
		    false,		//no boolean operation
		    0);			//copy number


  // Visualization attributes
  G4VisAttributes* worldVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0)); //White
  worldVisAtt->SetVisibility(true);
  fLogicWorld->SetVisAttributes(worldVisAtt);

  G4VisAttributes* worldVisAtt1 = new G4VisAttributes(G4Colour(0.0,1.0,0.0)); //Green
  worldVisAtt1->SetVisibility(true);
  logicTarget1->SetVisAttributes(worldVisAtt1);

  G4VisAttributes* worldVisAtt2 = new G4VisAttributes(G4Colour(1.0,0.0,0.0)); //Red
  worldVisAtt2->SetVisibility(true);
  logicTarget2->SetVisAttributes(worldVisAtt2);

  G4VisAttributes* worldVisAtt3 = new G4VisAttributes(G4Colour(1.0,0.0,0.0)); //Red
  worldVisAtt3->SetVisibility(true);
  logicTarget3->SetVisAttributes(worldVisAtt3);

  // Create Targets G4Regions and add logical volumes
  
  fRegion1 = new G4Region("Target1");
  fRegion2 = new G4Region("Target2");
  fRegion3 = new G4Region("Target3");
  
  G4ProductionCuts* cuts = new G4ProductionCuts();
  
  G4double defCut = 1*nanometer;
  cuts->SetProductionCut(defCut,"gamma");
  cuts->SetProductionCut(defCut,"e-");
  cuts->SetProductionCut(defCut,"e+");
  cuts->SetProductionCut(defCut,"proton");
  
  fRegion1->SetProductionCuts(cuts);
  fRegion1->AddRootLogicalVolume(logicTarget1); 

  fRegion2->SetProductionCuts(cuts);
  fRegion2->AddRootLogicalVolume(logicTarget2); 

  fRegion3->SetProductionCuts(cuts);
  fRegion3->AddRootLogicalVolume(logicTarget3); 

  return fPhysiWorld;
}
