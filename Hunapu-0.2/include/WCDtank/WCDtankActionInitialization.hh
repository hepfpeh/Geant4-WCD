#ifndef WCDtankActionInitialization_h
#define WCDtankActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class WCDtankActionInitialization : public G4VUserActionInitialization
{
  public:
    WCDtankActionInitialization();
    virtual ~WCDtankActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
