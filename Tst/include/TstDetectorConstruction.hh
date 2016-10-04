#ifndef TstDetectorConstruction_h
#define TstDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"


class G4LogicalVolume;
//class G4VPhysicalVolume;

class TstDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  // constructor and destructor.
  TstDetectorConstruction();
  virtual ~TstDetectorConstruction();

  // virtual method from G4VUserDetectorConstruction.
  virtual G4VPhysicalVolume* Construct();
  virtual void ConstructSDandField();

  G4LogicalVolume* GetScoringVolume() const { return ScoringVolume; }

  // Data members

  // Water cube (world)
  G4int WaterCube_xSizeHalf;
  G4int WaterCube_ySizeHalf;
  G4int WaterCube_zSizeHalf;

  // Tyvek foil
  G4int TyvekFoil_xSizeHalf;
  G4int TyvekFoil_ySizeHalf;
  G4int TyvekFoil_zSizeHalf;

  // GlassSlab
  G4int GlassSlab_xSizeHalf;
  G4int GlassSlab_ySizeHalf;
  G4int GlassSlab_zSizeHalf;

  // PMT

  // Glass sphere
  G4int GlassSphere_outerRadius;

  // Metal Sphere
  G4int MetalSphere_outerRadius;

  // Sensitive Volume

  G4LogicalVolume* SensitiveVolume;

protected:
  // Scoring volume
  G4LogicalVolume*  ScoringVolume;

};
#endif
