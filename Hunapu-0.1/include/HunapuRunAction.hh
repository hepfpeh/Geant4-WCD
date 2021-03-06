#ifndef HunapuRunAction_h
#define HunapuRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include <vector>

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class HunapuRunAction : public G4UserRunAction
{
  public:
    HunapuRunAction();
    virtual ~HunapuRunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
    inline std::vector<G4double>* GetVectorPointer() const { return G4dVectorPointer;}

  private:
    std::vector<G4double> G4dVector;
    std::vector<G4double>* G4dVectorPointer;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

