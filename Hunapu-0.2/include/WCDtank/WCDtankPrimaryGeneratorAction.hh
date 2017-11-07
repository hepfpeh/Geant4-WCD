#ifndef WCDtankPrimaryGeneratorAction_h
#define WCDtankPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"

class WCDtankPrimaryGeneratorMessenger;
class G4ParticleGun;
class G4Event;
class G4Box;
class G4Tubs;

enum Direction { Vertical, NonVertical, All };

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued
/// in front of the phantom across 80% of the (X,Y) phantom size.

class WCDtankPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    WCDtankPrimaryGeneratorAction();
    virtual ~WCDtankPrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);

    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

    // method to set particle direction
    void SetParticleDirection( G4String );

    // method to get particle azimuth angle
    G4double GetParticleAzimuthAngle() const { return ParticleAzimuthAngle; }

    // method to know if the particle direction is vertical
    G4bool GetParticleVerticalDirectionFlag() const { return PrimaryParticleDirectionIsVertical; }

  private:
    G4ParticleGun*  					fParticleGun; // pointer a to G4 gun class
    G4Tubs* 							WaterTube;
    G4Box* 								WorldBox;
    Direction 							ParticleDirection;
    WCDtankPrimaryGeneratorMessenger* 	fGunMessenger;
    G4double 							ParticleAzimuthAngle;
    G4bool		 						PrimaryParticleDirectionIsVertical;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


