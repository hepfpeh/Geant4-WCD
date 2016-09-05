#ifndef LXePMTSD_h
#define LXePMTSD_h 1

#include "G4DataVector.hh"
#include "G4VSensitiveDetector.hh"
#include "TstHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class TstSensitiveDetector : public G4VSensitiveDetector
{

  public:

	TstSensitiveDetector(G4String name);
    virtual ~TstSensitiveDetector();

    virtual void Initialize(G4HCofThisEvent* );
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* );

    virtual void EndOfEvent(G4HCofThisEvent* );
    virtual void clear();
    void DrawAll();
    void PrintAll();

  private:

    TstHit* TstSDHits;

};

#endif
