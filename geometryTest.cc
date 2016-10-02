

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifdef G4MULTITHREADED
  #include "G4MTRunManager.hh"
#else
  #include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"

#include "G4UIExecutive.hh"

#ifdef G4VIS_USE
  #include "G4VisExecutive.hh"
#endif

#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

int main(int argc,char** argv) 
{
  G4UIExecutive* session = NULL;
  if (argc==1)   // Define UI session for interactive mode.
  {
      session = new G4UIExecutive(argc, argv);
  }

  // Choose the Random engine
  
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  // Construct the default run manager
  
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  // runManager->SetNumberOfThreads(2); // Is equal to 2 by default
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  // Set mandatory user initialization classes
  DetectorConstruction* detector = new DetectorConstruction;
  runManager->SetUserInitialization(detector);
  
  runManager->SetUserInitialization(new PhysicsList);
  
  // User action initialization
  runManager->SetUserInitialization(new ActionInitialization(detector));
  
  // Initialize G4 kernel
  runManager->Initialize();
  
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  
  // Get the pointer to the User Interface manager 
  G4UImanager* UImanager = G4UImanager::GetUIpointer();  

  if (argc==1)   // Define UI session for interactive mode.
  {
    UImanager->ApplyCommand("/control/execute geometryTest.mac");
    session->SessionStart();
    delete session;
  }
  else           // Batch mode
  { 
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }

  delete visManager;

  delete runManager;

  return 0;
}

