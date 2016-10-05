#include "HunapuActionInitialization.hh"
#include "HunapuPrimaryGeneratorAction.hh"
#include "HunapuRunAction.hh"
#include "HunapuEventAction.hh"
#include "HunapuSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HunapuActionInitialization::HunapuActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HunapuActionInitialization::~HunapuActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HunapuActionInitialization::BuildForMaster() const
{
  SetUserAction(new HunapuRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HunapuActionInitialization::Build() const
{
  SetUserAction(new HunapuPrimaryGeneratorAction);
  SetUserAction(new HunapuRunAction);

  HunapuEventAction* eventAction = new HunapuEventAction;
  SetUserAction(eventAction);

  SetUserAction(new HunapuSteppingAction(eventAction));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
