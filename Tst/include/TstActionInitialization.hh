#ifndef TstActionInitialization_h
#define TstActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class TstActionInitialization : public G4VUserActionInitialization
{
  public:
    TstActionInitialization();
    virtual ~TstActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
