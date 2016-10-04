#ifndef TstSteppingAction_h
#define TstSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class TstEventAction;

class G4LogicalVolume;

/// Stepping action class
///

class TstSteppingAction : public G4UserSteppingAction
{
  public:
    TstSteppingAction(TstEventAction* eventAction);
    virtual ~TstSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    TstEventAction*  EventAction;
    G4LogicalVolume* ScoringVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
