#ifndef WCDtankEventAction_h
#define WCDtankEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///

class WCDtankEventAction : public G4UserEventAction
{
  public:
    WCDtankEventAction();
    virtual ~WCDtankEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddDepositedEnergy(G4double edep) { DepositedEnergy += edep; }
    void AddTrackLength(G4double tlen) { TrackLength += tlen; }

    G4int GetParticlePDGcode( ){ return PrimaryParticlePDGcode; }

  private:
    G4double     DepositedEnergy;
    G4double     TrackLength;
    G4String	 PrimaryParticleName;
    G4int		 PrimaryParticlePDGcode;
    G4double	 PrimaryParticleEnergy;
    G4double	 PrimaryParticleAzimuthAngle;
    G4bool		 PrimaryParticleIsVertical;

    G4int		 WCDtankSDHitsCollectionId;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
