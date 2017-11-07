#ifndef WCDtankSENSITIVEDETECTOR_H
#define WCDtankSENSITIVEDETECTOR_H 1

#include "G4DataVector.hh"
#include "G4VSensitiveDetector.hh"
#include "WCDtankHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class WCDtankSensitiveDetector : public G4VSensitiveDetector
{

  public:

	WCDtankSensitiveDetector(G4String name);
    virtual ~WCDtankSensitiveDetector();

    virtual void Initialize(G4HCofThisEvent* );
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* );

    virtual void EndOfEvent(G4HCofThisEvent* );
    virtual void clear();
    void DrawAll();
    void PrintAll();

  private:

    WCDtankHitsCollection* WCDtankSDHitsCollection;

};

#endif
