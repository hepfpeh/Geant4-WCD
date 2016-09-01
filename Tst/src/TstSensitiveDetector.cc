#include "TstSensitiveDetector.hh"
//#include "LXePMTHit.hh"
//#include "LXeDetectorConstruction.hh"
//#include "LXeUserTrackInformation.hh"

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

TstSensitiveDetector::TstSensitiveDetector(G4String name)
  : G4VSensitiveDetector(name)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TstSensitiveDetector::~TstSensitiveDetector() {}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TstSensitiveDetector::Initialize(G4HCofThisEvent*)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool TstSensitiveDetector::ProcessHits(G4Step* ,G4TouchableHistory* ){
	G4cout << "-o|o- Detection from TstSensitiveDetector::ProcessHits -o|o-" << G4endl;
  return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TstSensitiveDetector::EndOfEvent(G4HCofThisEvent* ) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TstSensitiveDetector::clear() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TstSensitiveDetector::DrawAll() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TstSensitiveDetector::PrintAll() {}
