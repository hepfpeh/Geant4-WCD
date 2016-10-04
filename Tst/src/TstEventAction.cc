#include "TstEventAction.hh"
#include "TstRun.hh"
#include "TstPrimaryGeneratorAction.hh"
#include "TstAnalysis.hh"
#include "TstHit.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SDManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TstEventAction::TstEventAction()
: G4UserEventAction(),
  DepositedEnergy(0.),
  TrackLength(0.),
  PrimaryParticlePDGcode(0.),
  PrimaryParticleEnergy(0.),
  TstSDHitsCollectionId(-1)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TstEventAction::~TstEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TstEventAction::BeginOfEventAction(const G4Event*)
{
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	if(TstSDHitsCollectionId<0)
		TstSDHitsCollectionId=SDman->GetCollectionID("pmtHitCollection");

	DepositedEnergy = 0;
	TrackLength = 0;
	// Run conditions
	//  note: There is no primary generator action object for "master"
	//        run manager for multi-threaded mode.
	const TstPrimaryGeneratorAction* generatorAction
		= static_cast<const TstPrimaryGeneratorAction*>
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

void TstEventAction::EndOfEventAction(const G4Event* anEvent)
{

	// Print the total amount of energy deposited in this event
	G4cout << "-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-" << G4endl;
	G4cout << "Primary particle PDG code: " << PrimaryParticlePDGcode << G4endl;
	G4cout << "Primary particle name: " << PrimaryParticleName << G4endl;
	G4cout << "Primary particle energy: " << G4BestUnit(PrimaryParticleEnergy,"Energy") << G4endl;
	G4cout << "Energy deposited: " << G4BestUnit(DepositedEnergy,"Energy") << G4endl;
	G4cout << "Track length: " << G4BestUnit(TrackLength,"Length") << G4endl;

	G4HCofThisEvent* hitsCE = anEvent->GetHCofThisEvent(); //Get the hit collections
	TstHitsCollection* pmtHC = 0;

	if(hitsCE){
		if(TstSDHitsCollectionId>=0) pmtHC = (TstHitsCollection*)(hitsCE->GetHC(TstSDHitsCollectionId));
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
