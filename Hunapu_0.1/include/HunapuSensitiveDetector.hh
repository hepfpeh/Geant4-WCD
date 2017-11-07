#ifndef LXePMTSD_h
#define LXePMTSD_h 1

#include "G4DataVector.hh"
#include "G4VSensitiveDetector.hh"
#include "HunapuHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class HunapuSensitiveDetector : public G4VSensitiveDetector
{

  public:

	HunapuSensitiveDetector(G4String name);
    virtual ~HunapuSensitiveDetector();

    virtual void Initialize(G4HCofThisEvent* );
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* );

    virtual void EndOfEvent(G4HCofThisEvent* );
    virtual void clear();
    void DrawAll();
    void PrintAll();

  private:

    HunapuHitsCollection* HunapuSDHitsCollection;

};

#endif
