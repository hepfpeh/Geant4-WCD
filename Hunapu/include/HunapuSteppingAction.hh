#ifndef HunapuSteppingAction_h
#define HunapuSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class HunapuEventAction;

class G4LogicalVolume;

/// Stepping action class
///

class HunapuSteppingAction : public G4UserSteppingAction
{
  public:
    HunapuSteppingAction(HunapuEventAction* eventAction);
    virtual ~HunapuSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    HunapuEventAction*  EventAction;
    G4LogicalVolume* ScoringVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
