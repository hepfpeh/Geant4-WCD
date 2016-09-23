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
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Make this appear first!
#include "G4Timer.hh"

#include "KinichAhauRunAction.hh"
#include "KinichAhauRun.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

KinichAhauRunAction::KinichAhauRunAction()
 : G4UserRunAction(),
   fTimer(0), fElapsedTime(0)
{
  fTimer = new G4Timer;
}

//sd....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

KinichAhauSensitiveDetector::KinichAhauSensitiveDetector(const G4String& name)
  : G4VSensitiveDetector(name),  ftimer(0), fElapsedTime(0), KinichAhauSDHits(0)
{ }

//sd....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

KinichAhauSensitiveDetector::~KinichAhauSensitiveDetector() {}

//sd....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void KinichAhauSensitiveDetector::Initialize(G4HCofThisEvent*)
{ }

//sd....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool KinichAhauSensitiveDetector::ProcessHits(G4Step* ,G4TouchableHistory* ){
	fTimer -> Stop();
//	fElapsedTime += fTimer -> GetRealElapsed();
	G4cout  << "-o|o- Detection from KinichAhauRunAction::ProcessHits -o|o-"
		<< " time= " << fTimer -> GetRealElapsed() << "s"
		<< G4endl;
	fTimer -> Start();
  return false;
}

//sd....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void KinichAhauSensitiveDetector::EndOfEvent(G4HCofThisEvent* ) {
	G4int NumberOfPhotons = 0;
	if ( KinichAhauSDHits ) NumberOfPhotons = KinichAhauSDHits->GetPhotonCount();
	G4cout << "Detections: " << NumberOfPhotons << G4endl;
	delete KinichAhauSDHits;
	KinichAhauSDHits = 0;
}

//sd....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void KinichAhauSensitiveDetector::clear() {}

//sd....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void KinichAhauSensitiveDetector::DrawAll() {}

//sd....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void KinichAhauSensitiveDetector::PrintAll() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* KinichAhauRunAction::GenerateRun()
{
  return new KinichAhauRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

KinichAhauRunAction::~KinichAhauRunAction()
{
  delete fTimer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void KinichAhauRunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  fTimer->Start();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void KinichAhauRunAction::EndOfRunAction(const G4Run* aRun)
{
  fTimer->Stop();
  G4cout << "number of event = " << aRun->GetNumberOfEvent()
         << " " << *fTimer << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
