#ifndef WCDtankRun_h
#define WCDtankRun_h 1

#include "G4Run.hh"
#include "globals.hh"

class G4Event;

/// Run class
///

class WCDtankRun : public G4Run
{
  public:
    WCDtankRun();
    virtual ~WCDtankRun();

    // method from the base class
    virtual void Merge(const G4Run*);

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

