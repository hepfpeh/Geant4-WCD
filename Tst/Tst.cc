//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file runAndEvent/RE02/RE02.cc
/// \brief Main program of the runAndEvent/RE02 example
//
//
// $Id: RE02.cc 76292 2013-11-08 13:10:20Z gcosmo $
//
// 

#include "TstDetectorConstruction.hh"
#include "TstPhysicsList.hh"
#include "TstActionInitialization.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//
int main(int argc,char** argv) {

  // Run manager
  G4RunManager * runManager = new G4RunManager;

  // UserInitialization classes (mandatory)
  //---
  //  Create Detector
  TstDetectorConstruction* detector = new TstDetectorConstruction;
  runManager->SetUserInitialization(detector);
  //
  runManager->SetUserInitialization(new TstPhysicsList);
  
  // UserAction classes
  runManager->SetUserInitialization(new TstActionInitialization);

  //Initialize G4 kernel
  runManager->Initialize();

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();
      
  //get the pointer to the User Interface manager 
  G4UImanager * pUI = G4UImanager::GetUIpointer();  

  if(argc==1)
  // Define (G)UI terminal for interactive mode  
  { 
     G4UIExecutive* ui = new G4UIExecutive(argc, argv);
     pUI->ApplyCommand("/control/execute vis.mac");
     ui->SessionStart();
     delete ui;
  }
  else
  // Batch mode
  { 
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    pUI->ApplyCommand(command+fileName);
  }

  delete visManager;
  delete runManager;

  return 0;
}

//

