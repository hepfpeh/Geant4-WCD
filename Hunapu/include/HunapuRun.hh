#ifndef HunapuRun_h
#define HunapuRun_h 1

#include "G4Run.hh"
#include "globals.hh"

class G4Event;

/// Run class
///

class HunapuRun : public G4Run
{
  public:
    HunapuRun();
    virtual ~HunapuRun();

    // method from the base class
    virtual void Merge(const G4Run*);

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

