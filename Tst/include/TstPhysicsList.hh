#ifndef TstPhysicsList_h
#define TstPhysicsList_h 1

#include "globals.hh"
#include "G4VUserPhysicsList.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TstPhysicsList : public G4VUserPhysicsList
{
  public:
    TstPhysicsList();
    virtual ~TstPhysicsList();

  public:
    virtual void ConstructParticle();
    virtual void ConstructProcess();

    virtual void SetCuts();

    //these methods Construct physics processes and register them
    void ConstructDecay();
    void ConstructEM();
    void ConstructOp();

  private:
    G4int                fVerboseLebel;
    G4int fMaxNumPhotonStep;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /* Hunapu_0_PhysicsList_h */
