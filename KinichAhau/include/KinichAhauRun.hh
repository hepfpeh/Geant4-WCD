#ifndef KinichAhauRun_h
#define KinichAhauRun_h 1

#include "G4Run.hh"
#include "globals.hh"

class G4Event;

/// Run class
///

class KinichAhauRun : public G4Run
{
  public:
    KinichAhauRun();
    virtual ~KinichAhauRun();
  public:
    void SumTrackLength (G4int,G4int,G4double,G4double,G4double,G4double);

    // method from the base class
    virtual void Merge(const G4Run*);

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
