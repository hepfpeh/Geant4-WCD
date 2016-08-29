#include "TstActionInitialization.hh"
#include "TstPrimaryGeneratorAction.hh"
#include "TstRunAction.hh"
#include "TstEventAction.hh"
#include "TstSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TstActionInitialization::TstActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TstActionInitialization::~TstActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TstActionInitialization::BuildForMaster() const
{
  SetUserAction(new TstRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TstActionInitialization::Build() const
{
  SetUserAction(new TstPrimaryGeneratorAction);
  SetUserAction(new TstRunAction);

  TstEventAction* eventAction = new TstEventAction;
  SetUserAction(eventAction);

  SetUserAction(new TstSteppingAction(eventAction));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
