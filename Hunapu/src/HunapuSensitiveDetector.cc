#include "HunapuSensitiveDetector.hh"
#include "HunapuAnalysis.hh"
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

HunapuSensitiveDetector::HunapuSensitiveDetector(G4String name)
  : G4VSensitiveDetector(name),  HunapuSDHitsCollection(0)
{
	  collectionName.insert("pmtHitCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HunapuSensitiveDetector::~HunapuSensitiveDetector() {}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HunapuSensitiveDetector::Initialize(G4HCofThisEvent* hitsCE)
{
	  HunapuSDHitsCollection = new HunapuHitsCollection
	                      (SensitiveDetectorName,collectionName[0]);
	  //Store collection with event and keep ID
	  static G4int hitCID = -1;
	  if(hitCID<0){
	    hitCID = GetCollectionID(0);
	  }
	  hitsCE->AddHitsCollection( hitCID, HunapuSDHitsCollection );

	  HunapuHit* hit = new HunapuHit;
	  HunapuSDHitsCollection->insert(hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool HunapuSensitiveDetector::ProcessHits(G4Step* ,G4TouchableHistory* ){
	HunapuHit* hit = new HunapuHit;
	hit = (*HunapuSDHitsCollection)[0];
	hit->IncPhotonCount();
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HunapuSensitiveDetector::EndOfEvent(G4HCofThisEvent* ) {
/*
	// get analysis manager
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	G4int NumberOfPhotons = 0;
	if ( HunapuSDHits ) NumberOfPhotons = HunapuSDHits->GetPhotonCount();
	G4cout << "-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-" << G4endl;
	G4cout << "Photons detected in this event: " << NumberOfPhotons << G4endl;
//	G4cout << NumberOfPhotons << G4endl;

	// fill histograms
	analysisManager->FillH1(1, NumberOfPhotons);

	// fill ntuple
	analysisManager->FillNtupleDColumn(0, NumberOfPhotons);
	analysisManager->AddNtupleRow();

	delete HunapuSDHits;
	HunapuSDHits = 0;
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HunapuSensitiveDetector::clear() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HunapuSensitiveDetector::DrawAll() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HunapuSensitiveDetector::PrintAll() {}
