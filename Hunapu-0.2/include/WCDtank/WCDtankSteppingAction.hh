#ifndef WCDtankSteppingAction_h
#define WCDtankSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class WCDtankEventAction;

class G4LogicalVolume;

/// Stepping action class
///

class WCDtankSteppingAction : public G4UserSteppingAction
{
  public:
    WCDtankSteppingAction(WCDtankEventAction* eventAction);
    virtual ~WCDtankSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    WCDtankEventAction*  EventAction;
    G4LogicalVolume* ScoringVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
