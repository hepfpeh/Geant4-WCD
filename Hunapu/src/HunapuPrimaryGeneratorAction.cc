
#include "HunapuPrimaryGeneratorAction.hh"
#include "HunapuPrimaryGeneratorMessenger.hh"
#include "HunapuRandom.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4String.hh"

#include "Randomize.hh"

#include <cmath>
#include <map>


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HunapuPrimaryGeneratorAction::HunapuPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),
  WaterTube(0),
  WorldBox(0),
  ParticleDirection(All),
  fGunMessenger(0),
  ParticleAzimuthAngle(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="opticalphoton");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1.0,-1.0,0.0));
  fParticleGun->SetParticlePosition(G4ThreeVector(0.0*m,0.0*m,0.0*m));
  fParticleGun->SetParticleEnergy(3.0*eV);

  //create a messenger for this class
  fGunMessenger = new HunapuPrimaryGeneratorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HunapuPrimaryGeneratorAction::~HunapuPrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HunapuPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	  //this function is called at the begining of ecah event
	  //

	  // In order to avoid dependence of PrimaryGeneratorAction
	  // on DetectorConstruction class we get solid_WaterTube volume
	  // from G4LogicalVolumeStore.


	  G4double WaterTube_radius = 0;
	  G4double WaterTube_halfHeight = 0;

	  if (!WaterTube)
	  {
	    G4LogicalVolume* WT_LV
	      = G4LogicalVolumeStore::GetInstance()->GetVolume("WaterTube_logic");
	    if ( WT_LV ) WaterTube = dynamic_cast<G4Tubs*>(WT_LV->GetSolid());
	  }

	  if ( WaterTube ) {
	    WaterTube_radius = WaterTube->GetOuterRadius();
	    WaterTube_halfHeight = WaterTube->GetZHalfLength();
	  }
	  else  {
	    G4ExceptionDescription msg;
	    msg << "Water Tube volume of G4tubs shape not found.\n";
	    msg << "Perhaps you have changed geometry.\n";
	    msg << "The gun will be place at the center.";
	    G4Exception("HunapuPrimaryGeneratorAction::GeneratePrimaries()",
	     "MyCode0002",JustWarning,msg);
	  }

	  // Verificando las dimensiones del mundo.

	  G4double WorldBox_halfSize;

	  if (!WorldBox)
	  {
	    G4LogicalVolume* WB_LV
	      = G4LogicalVolumeStore::GetInstance()->GetVolume("WorldCube_logic");
	    if ( WB_LV ) WorldBox = dynamic_cast<G4Box*>(WB_LV->GetSolid());
	  }

	  if ( WorldBox ) {
	    WorldBox_halfSize = WorldBox->GetXHalfLength();
	  }
	  else  {
	    G4ExceptionDescription msg;
	    msg << "World volume of G4box shape not found.\n";
	    msg << "Perhaps you have changed geometry.\n";
	    msg << "The gun will be place at the center.";
	    G4Exception("HunapuPrimaryGeneratorAction::GeneratePrimaries()",
	     "MyCode0003",JustWarning,msg);
	  }

	  /*
	   * Generacion de parametros aleatorios
	   * ===================================
	   *
	   * Se generan los siguientes numeros aleatorios uniformentente distribuidos
	   *
	   * cil_r 		: coordenada cilindrica r en el rango 0 <= r <= WaterTube_radius
	   * cil_z 		: coordenada cilindrica z en el rango -G4double WaterTube_halfHeight <= z <= +G4double WaterTube_halfHeight
	   * cil_phi	: coordenada cilindrica phi en el rango 0 <= phi <= 2pi
	   *
	   * Las coordenadas cilindricas son de un punto dentro del volumen de agua en el que pasara la particula.
	   *
	   */

	  G4double cil_r 		= ( G4UniformRand() * WaterTube_radius );
	  G4double cil_z 		= ( ( G4UniformRand() - 0.5 ) * WaterTube_halfHeight );
	  G4double cil_phi		= ( G4UniformRand() * twopi );

	  /*
	   *
	   * ang_theta	: angulo azimutal theta de la particula incidente en el rango 0 <= theta <= pi/2
	   *
	   * El angulo azimutal se distribulle con cos^2.
	   *
	   */

	  G4double ang_theta	= CosSqrDistRand();

	  /*
	   * Muones verticales
	   * =================
	   *
	   * Se consideran muones verticales a aquellos que entran por la tapa superior del cilindro de agua y salen por
	   * la inferior. La condicion que se debe verificar para esto es que ang_theta < min( theta_c0, theta_c1 ), donde
	   * theta_c0, theta_c1 son angulos criticos que dependen de las dimenciones del cilindro de agua y de las coordenadas
	   * cilindricas cil_r y cil_z.
	   *
	   */

	  G4double theta_c0 = std::atan( ( WaterTube_radius - cil_r ) / ( WaterTube_halfHeight - cil_z ) );
	  G4double theta_c1 = std::atan( ( WaterTube_radius + cil_r ) / ( WaterTube_halfHeight + cil_z ) );

	  G4double theta_crit = ( (theta_c0 < theta_c1 )? theta_c0 : theta_c1 );

	  switch( ParticleDirection )
	  {
	  	  case Vertical	:
	  		while ( ang_theta > theta_crit )
	  					  ang_theta	= CosSqrDistRand();
	  		break;
	  	  case NonVertical :
		  		while ( ang_theta < theta_crit )
		  					  ang_theta	= CosSqrDistRand();
		  		break;
	  	  case All :
	  		  break;
	  }

	  ParticleAzimuthAngle = ang_theta;

	  /*
	   * Coordenadas de la pistola de particulas
	   * =======================================
	   *
	   * La pistola de particulas (ParticleGun) se coloca sobre una semiesfera que rodea la parte superior del cilindro de agua y lanza
	   * las particulas hacia este.
	   *
	   * ParticleGun_Sphere_radius	: Radio de la semiesfera donde se coloca la pistola.
	   *
	   * ParticleGun_xCoordinate	: coordenada x de la pistola.
	   * ParticleGun_yCoordinate	: coordenada y de la pistola.
	   * ParticleGun_zCorrdinate	: coordenada z de la pistola.
	   *
	   * ParticleGun_xDirection		: componente x del vector unitario de direccion del lanzamiento.
	   * ParticleGun_yDirection		: componente y del vector unitario de direccion del lanzamiento.
	   * ParticleGun_zDirection		: componente z del vector unitario de direccion del lanzamiento.
	   *
	   */

	  G4double ParticleGun_Sphere_radius = 1.00*m;

	  if ( ParticleGun_Sphere_radius > WorldBox_halfSize ) {
		G4ExceptionDescription msg;
		msg << "Particle can not be throw from outside the world!.\n";
		msg << "Perhaps you have changed geometry.";
		G4Exception("HunapuPrimaryGeneratorAction::GeneratePrimaries()",
		 "MyCode0003",JustWarning,msg);
	  }

	  G4double SinPhi = std::sin( cil_phi );
	  G4double CosPhi = std::cos( cil_phi );

	  G4double SinTheta = std::sin( ang_theta );
	  G4double CosTheta = std::cos( ang_theta );

	  G4double SinAlpha = ( cil_r * CosTheta - cil_z * SinTheta ) / ParticleGun_Sphere_radius;
	  G4double CosAlpha = std::sqrt( 1.0 - SinAlpha*SinAlpha );

	  G4double SinVarTheta = SinAlpha * CosTheta + CosAlpha * SinTheta;
	  G4double CosVarTheta = CosAlpha * CosTheta - SinAlpha * SinTheta;

	  G4double ParticleGun_xCoordinate = ParticleGun_Sphere_radius * SinVarTheta * CosPhi;
	  G4double ParticleGun_yCoordinate = ParticleGun_Sphere_radius * SinVarTheta * SinPhi;
	  G4double ParticleGun_zCoordinate = ParticleGun_Sphere_radius * CosVarTheta;

	  G4double ParticleGun_xDirection = - SinTheta * CosPhi;
	  G4double ParticleGun_yDirection = - SinTheta * SinPhi;
	  G4double ParticleGun_zDirection = - CosTheta;


	  fParticleGun->SetParticlePosition( G4ThreeVector( ParticleGun_xCoordinate , ParticleGun_yCoordinate , ParticleGun_zCoordinate ) );
	  fParticleGun->SetParticleMomentumDirection( G4ThreeVector( ParticleGun_xDirection , ParticleGun_yDirection , ParticleGun_zDirection ) );

	  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HunapuPrimaryGeneratorAction::SetParticleDirection(G4String aDirection)
{
	std::map< G4String, Direction > aMap;

    aMap["Vertical"] 	= Vertical;
    aMap["NonVertical"] = NonVertical;
    aMap["All"] 		= All;

    ParticleDirection = aMap[ aDirection ];
}
