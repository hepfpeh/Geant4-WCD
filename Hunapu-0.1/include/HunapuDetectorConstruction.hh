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
  G4int WorldCube_SizeHalf;

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

  // This parameters are common to all PMTs volumes
  G4double innerRadius;
  G4double startPhiAngle;
  G4double deltaPhiAngle;
  G4double startThetaAngle;
  G4double deltaThetaAngle;

  // Glass SemiSphere
  G4double GlassSemiSphere_outerRadius;

  // Metal Sphere
  G4double MetalSemiSphere_outerRadius;

  // Vacuum Sphere
  G4double VacuumSemiSphere_outerRadius;

  // Sensitive Volume

  G4LogicalVolume* SensitiveVolume;

protected:
  // Scoring volume
  G4LogicalVolume*  ScoringVolume;

};
#endif
