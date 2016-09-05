#include "TstSteppingAction.hh"
#include "TstEventAction.hh"
#include "TstDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4OpBoundaryProcess.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TstSteppingAction::TstSteppingAction(TstEventAction* )
: G4UserSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TstSteppingAction::~TstSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TstSteppingAction::UserSteppingAction(const G4Step* theStep)
{

/*	G4Track* theTrack = theStep->GetTrack();

	G4StepPoint* thePrePoint = theStep->GetPreStepPoint();
	G4VPhysicalVolume* thePrePV = thePrePoint->GetPhysicalVolume();

	  G4OpBoundaryProcessStatus boundaryStatus=Undefined;
	  static G4ThreadLocal G4OpBoundaryProcess* boundary=NULL;

	  G4StepPoint* thePostPoint = theStep->GetPostStepPoint();
	  G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();

	  //find the boundary process only once
	  if(!boundary){
	    G4ProcessManager* pm
	      = theStep->GetTrack()->GetDefinition()->GetProcessManager();
	    G4int nprocesses = pm->GetProcessListLength();
	    G4ProcessVector* pv = pm->GetProcessList();
	    G4int i;
	    for( i=0;i<nprocesses;i++){
	      if((*pv)[i]->GetProcessName()=="OpBoundary"){
	        boundary = (G4OpBoundaryProcess*)(*pv)[i];
	        break;
	      }
	    }
	  }

	  if(!thePostPV) return;

	  G4ParticleDefinition* particleType = theTrack->GetDefinition();
	    if(particleType==G4OpticalPhoton::OpticalPhotonDefinition()){
	      //Optical photon only


	    boundaryStatus=boundary->GetStatus();

	    //Check to see if the partcile was actually at a boundary
	    //Otherwise the boundary status may not be valid
	    //Prior to Geant4.6.0-p1 this would not have been enough to check
	    if(thePostPoint->GetStepStatus()==fGeomBoundary){
	      if(boundaryStatus == Detection )
	      {
	    	G4cout << "-o|o- Detection form TstSteppingAction::UserSteppingAction -o|o-" << G4endl ;
	      }
	    }
	}
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

