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

#include "G4Timer.hh"
#include "KinichAhauSensitiveDetector.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

KinichAhauSensitiveDetector::KinichAhauSensitiveDetector(const G4String& name)
  : G4VSensitiveDetector(name),  KinichAhauSDHits(0), fTimer(0), fElapsedTime(0)
{
  fTimer = new G4Timer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

KinichAhauSensitiveDetector::~KinichAhauSensitiveDetector() {}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void KinichAhauSensitiveDetector::Initialize(G4HCofThisEvent*)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool KinichAhauSensitiveDetector::ProcessHits(G4Step* ,G4TouchableHistory* ){
	fTimer -> Stop();
//	fElapsedTime += fTimer -> GetRealElapsed();
	G4cout  << "-o|o- Detection from KinichAhauSensitiveDetector::ProcessHits -o|o-"
		<< " time= " << fTimer -> GetRealElapsed() << "s"
		<< G4endl;
	fTimer -> Start();
  return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void KinichAhauSensitiveDetector::EndOfEvent(G4HCofThisEvent* ) {
	G4int NumberOfPhotons = 0;
	if ( KinichAhauSDHits ) NumberOfPhotons = KinichAhauSDHits->GetPhotonCount();
	G4cout << "Detections: " << NumberOfPhotons << G4endl;
	delete KinichAhauSDHits;
	KinichAhauSDHits = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void KinichAhauSensitiveDetector::clear() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void KinichAhauSensitiveDetector::DrawAll() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void KinichAhauSensitiveDetector::PrintAll() {}
