#ifndef HunapuDetectorConstruction_h
#define HunapuDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"


class G4LogicalVolume;
//class G4VPhysicalVolume;

class HunapuDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  // constructor and destructor.
  HunapuDetectorConstruction();
  virtual ~HunapuDetectorConstruction();

  // virtual method from G4VUserDetectorConstruction.
  virtual G4VPhysicalVolume* Construct();
  virtual void ConstructSDandField();

  G4LogicalVolume* GetScoringVolume() const { return ScoringVolume; }

  // Data members

  // World cube
  G4int WorldCube_xSizeHalf;
  G4int WorldCube_ySizeHalf;
  G4int WorldCube_zSizeHalf;

  // Tyvek tube
  G4double TyvekTube_innerRadious;
  G4double TyvekTube_outerRadious;
  G4double TyvekTube_halfHeight;
  G4double TyvekTube_startAngle;
  G4double TyvekTube_spannAngle;


  // Water tube
  G4double WaterTube_innerRadious;
  G4double WaterTube_outerRadious;
  G4double WaterTube_halfHeight;
  G4double WaterTube_startAngle;
  G4double WaterTube_spannAngle;

  // PMT

  // Glass SemiSphere
  G4double GlassSemiSphere_outerRadius;
  G4double GlassSemiSphere_innerRadius;
  G4double GlassSemiSphere_startPhiAngle;
  G4double GlassSemiSphere_endPhiAngle;
  G4double GlassSemiSphere_startThetaAngle;
  G4double GlassSemiSphere_deltaThetaAngle;

  // Metal Sphere
  G4double MetalSemiSphere_outerRadius;
  G4double MetalSemiSphere_innerRadius;
  G4double MetalSemiSphere_startPhiAngle;
  G4double MetalSemiSphere_endPhiAngle;
  G4double MetalSemiSphere_startThetaAngle;
  G4double MetalSemiSphere_deltaThetaAngle;

  // Sensitive Volume

  G4LogicalVolume* SensitiveVolume;

protected:
  // Scoring volume
  G4LogicalVolume*  ScoringVolume;

};
#endif
