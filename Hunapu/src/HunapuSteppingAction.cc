#include "HunapuSteppingAction.hh"
#include "HunapuEventAction.hh"
#include "HunapuDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4OpBoundaryProcess.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HunapuSteppingAction::HunapuSteppingAction(HunapuEventAction* eventAction)
: G4UserSteppingAction(),
  EventAction(eventAction),
  ScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HunapuSteppingAction::~HunapuSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HunapuSteppingAction::UserSteppingAction(const G4Step* theStep)
{
	  if (!ScoringVolume) {
	    const HunapuDetectorConstruction* detectorConstruction
	      = static_cast<const HunapuDetectorConstruction*>
	        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	    ScoringVolume = detectorConstruction->GetScoringVolume();
	  }

	  // get volume of the current step
	  G4LogicalVolume* volume
	    = theStep->GetPreStepPoint()->GetTouchableHandle()
	      ->GetVolume()->GetLogicalVolume();

	  // check if we are in scoring volume
	  if (volume != ScoringVolume) return;

	  // collect energy deposited in this step
	  G4double edepStep = theStep->GetTotalEnergyDeposit();
	  EventAction->AddDepositedEnergy(edepStep);

	  // step length
		G4double stepLength = 0.;
		if ( theStep->GetTrack()->GetDefinition()->GetPDGEncoding() == EventAction->GetParticlePDGcode() ) {
		  stepLength = theStep->GetStepLength();
		}
		EventAction->AddTrackLength(stepLength);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

