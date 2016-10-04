#include "TstSensitiveDetector.hh"
#include "TstAnalysis.hh"
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
  : G4VSensitiveDetector(name),  TstSDHitsCollection(0)
{
	  collectionName.insert("pmtHitCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TstSensitiveDetector::~TstSensitiveDetector() {}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TstSensitiveDetector::Initialize(G4HCofThisEvent* hitsCE)
{
	  TstSDHitsCollection = new TstHitsCollection
	                      (SensitiveDetectorName,collectionName[0]);
	  //Store collection with event and keep ID
	  static G4int hitCID = -1;
	  if(hitCID<0){
	    hitCID = GetCollectionID(0);
	  }
	  hitsCE->AddHitsCollection( hitCID, TstSDHitsCollection );

	  TstHit* hit = new TstHit;
	  TstSDHitsCollection->insert(hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool TstSensitiveDetector::ProcessHits(G4Step* ,G4TouchableHistory* ){
	TstHit* hit = new TstHit;
	hit = (*TstSDHitsCollection)[0];
	hit->IncPhotonCount();
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TstSensitiveDetector::EndOfEvent(G4HCofThisEvent* ) {
/*
	// get analysis manager
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	G4int NumberOfPhotons = 0;
	if ( TstSDHits ) NumberOfPhotons = TstSDHits->GetPhotonCount();
	G4cout << "-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-" << G4endl;
	G4cout << "Photons detected in this event: " << NumberOfPhotons << G4endl;
//	G4cout << NumberOfPhotons << G4endl;

	// fill histograms
	analysisManager->FillH1(1, NumberOfPhotons);

	// fill ntuple
	analysisManager->FillNtupleDColumn(0, NumberOfPhotons);
	analysisManager->AddNtupleRow();

	delete TstSDHits;
	TstSDHits = 0;
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TstSensitiveDetector::clear() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TstSensitiveDetector::DrawAll() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TstSensitiveDetector::PrintAll() {}
