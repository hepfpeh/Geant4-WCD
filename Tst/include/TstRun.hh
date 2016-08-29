#ifndef TstRun_h
#define TstRun_h 1

#include "G4Run.hh"
#include "globals.hh"

class G4Event;

/// Run class
///

class TstRun : public G4Run
{
  public:
    TstRun();
    virtual ~TstRun();

    // method from the base class
    virtual void Merge(const G4Run*);

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

