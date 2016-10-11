#ifndef HunapuPrimaryGeneratorAction_h
#define HunapuPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"

class G4ParticleGun;
class G4Event;
class G4Box;
class G4Tubs;

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued
/// in front of the phantom across 80% of the (X,Y) phantom size.

class HunapuPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    HunapuPrimaryGeneratorAction();
    virtual ~HunapuPrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);

    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    G4Tubs* WaterTube;
    G4Box* WorldBox;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


