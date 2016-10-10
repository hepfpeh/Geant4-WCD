#include "HunapuEventAction.hh"
#include "HunapuRun.hh"
#include "HunapuPrimaryGeneratorAction.hh"
#include "HunapuAnalysis.hh"
#include "HunapuHit.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SDManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HunapuEventAction::HunapuEventAction()
: G4UserEventAction(),
  DepositedEnergy(0.),
  TrackLength(0.),
  PrimaryParticlePDGcode(0.),
  PrimaryParticleEnergy(0.),
  HunapuSDHitsCollectionId(-1)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HunapuEventAction::~HunapuEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HunapuEventAction::BeginOfEventAction(const G4Event*)
{
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	if(HunapuSDHitsCollectionId<0)
		HunapuSDHitsCollectionId=SDman->GetCollectionID("pmtHitCollection");

	DepositedEnergy = 0;
	TrackLength = 0;
	// Run conditions
	//  note: There is no primary generator action object for "master"
	//        run manager for multi-threaded mode.
	const HunapuPrimaryGeneratorAction* generatorAction
		= static_cast<const HunapuPrimaryGeneratorAction*>
	 	 (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
	if (generatorAction)
	{
		const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
		PrimaryParticleName = particleGun->GetParticleDefinition()->GetParticleName();
		PrimaryParticlePDGcode = particleGun->GetParticleDefinition()->GetPDGEncoding();
		PrimaryParticleEnergy = particleGun->GetParticleEnergy();
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HunapuEventAction::EndOfEventAction(const G4Event* anEvent)
{

	// Print the total amount of energy deposited in this event
	G4cout << "-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-" << G4endl;
	G4cout << "Primary particle PDG code: " << PrimaryParticlePDGcode << G4endl;
	G4cout << "Primary particle name: " << PrimaryParticleName << G4endl;
	G4cout << "Primary particle energy: " << G4BestUnit(PrimaryParticleEnergy,"Energy") << G4endl;
	G4cout << "Energy deposited: " << G4BestUnit(DepositedEnergy,"Energy") << G4endl;
	G4cout << "Track length: " << G4BestUnit(TrackLength,"Length") << G4endl;

	G4HCofThisEvent* hitsCE = anEvent->GetHCofThisEvent(); //Get the hit collections
	HunapuHitsCollection* pmtHC = 0;

	if(hitsCE){
		if(HunapuSDHitsCollectionId>=0) pmtHC = (HunapuHitsCollection*)(hitsCE->GetHC(HunapuSDHitsCollectionId));
	}

	G4int NumberOfPhotons = (*pmtHC)[0]->GetPhotonCount();
	G4cout << "Photons detected in this event: " << NumberOfPhotons << G4endl;

	// get analysis manager
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	// fill histograms
	analysisManager->FillH1(1, NumberOfPhotons);

	// fill ntuple
	analysisManager->FillNtupleDColumn(0, PrimaryParticleEnergy);
	analysisManager->FillNtupleDColumn(1, DepositedEnergy);
	analysisManager->FillNtupleDColumn(2, TrackLength);
	analysisManager->FillNtupleDColumn(3, NumberOfPhotons);
	analysisManager->AddNtupleRow();

	(*pmtHC)[0]->ResetPhotonCount();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
