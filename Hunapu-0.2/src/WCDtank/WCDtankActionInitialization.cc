#include "WCDtankActionInitialization.hh"
#include "WCDtankPrimaryGeneratorAction.hh"
#include "WCDtankRunAction.hh"
#include "WCDtankEventAction.hh"
#include "WCDtankSteppingAction.hh"
#include "WCDtankStackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WCDtankActionInitialization::WCDtankActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WCDtankActionInitialization::~WCDtankActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WCDtankActionInitialization::BuildForMaster() const
{
  SetUserAction(new WCDtankRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WCDtankActionInitialization::Build() const
{
  SetUserAction(new WCDtankPrimaryGeneratorAction);
  SetUserAction(new WCDtankRunAction);

  WCDtankEventAction* eventAction = new WCDtankEventAction;
  SetUserAction(eventAction);

  SetUserAction(new WCDtankSteppingAction(eventAction));
//  SetUserAction(new WCDtankStackingAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
