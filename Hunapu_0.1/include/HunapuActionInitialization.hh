#ifndef HunapuActionInitialization_h
#define HunapuActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class HunapuActionInitialization : public G4VUserActionInitialization
{
  public:
    HunapuActionInitialization();
    virtual ~HunapuActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
