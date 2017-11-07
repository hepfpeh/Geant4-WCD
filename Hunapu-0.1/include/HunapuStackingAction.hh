/*
 * HunapuStakingAction.hh
 *
 *  Created on: 17/10/2016
 *      Author: hepf
 */

#ifndef HUNAPUSTACKINGACTION_HH_
#define HUNAPUSTACKINGACTION_HH_

#include "globals.hh"
#include "G4UserStackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HunapuStackingAction : public G4UserStackingAction
{
  public:
    HunapuStackingAction();
    virtual ~HunapuStackingAction();

  public:
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    virtual void NewStage();
    virtual void PrepareNewEvent();

  private:
    G4int fScintillationCounter;
    G4int fCerenkovCounter;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



#endif /* HUNAPUSTACKINGACTION_HH_ */
