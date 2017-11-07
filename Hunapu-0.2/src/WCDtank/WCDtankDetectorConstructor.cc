#include "WCDtankDetectorConstruction.hh"
#include "WCDtankSensitiveDetector.hh"

#include "G4RunManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
//#include "G4Cons.hh"
//#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
//#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VSensitiveDetector.hh"

#include "G4PhysicalConstants.hh"

#include "G4SDManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WCDtankDetectorConstruction::WCDtankDetectorConstruction()
: G4VUserDetectorConstruction()
{

	// World cube (world)
	WorldCube_SizeHalf	= 1.50*m;

	// Tyvek tube
	TyvekTube_innerRadious	= 0.00 *cm;
	TyvekTube_outerRadious	= 25.05 *cm;
	TyvekTube_halfHeight	= 30.05*cm;
	TyvekTube_startAngle	= 0.00 *deg;
	TyvekTube_spannAngle	= 360  *deg;

	// Water tube
	WaterTube_innerRadious	= 0.00 *cm;
	WaterTube_outerRadious	= 25.0 *cm;
	WaterTube_halfHeight	= 30.0*cm;
	WaterTube_startAngle	= 0.00 *deg;
	WaterTube_spannAngle	= 360  *deg;

	// PMT

	innerRadius		= 0.00	*cm;
	startPhiAngle	= 0.00	*deg;
	deltaPhiAngle	= 360.	*deg;
	startThetaAngle	= 90.0	*deg;
	deltaThetaAngle	= 90.0	*deg;


	// Glass sphere
	GlassSemiSphere_outerRadius		= 11.4	*cm;

	// Metal Sphere
	MetalSemiSphere_outerRadius		= 11.35	*cm;

	// Vacuum Sphere
	VacuumSemiSphere_outerRadius	= 11.3	*cm;

	  // Sensitive Volume

	  SensitiveVolume = 0;

	  // Scoring volume
	  ScoringVolume = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WCDtankDetectorConstruction::~WCDtankDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* WCDtankDetectorConstruction::Construct()
{

  // Some elements
  G4double a, z, density, temperature, pressure;
  G4int nelements;

  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);


  // Vacuum
  //
  G4Material* vacuum = new G4Material("vacuum", z=1., a=1.01*g/mole, density=universe_mean_density, kStateGas, temperature = 0.1*kelvin, pressure = 1.e-19*pascal);

  // Air
  //

  G4Material* air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
  air->AddElement(N, 70.*perCent);
  air->AddElement(O, 30.*perCent);

  // Water material
  G4Material* water = new G4Material("Water", density= 1.0*g/cm3, nelements=2);
  water->AddElement(H, 2);
  water->AddElement(O, 1);

  //Tyvek

  G4NistManager* nist = G4NistManager::Instance();
  G4Material* tyvek = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

  //Glass

  G4Material* glass = nist->FindOrBuildMaterial("G4_Pyrex_Glass");

  // Aluminium

  G4Material* aluminium = new G4Material("Aluminium",z=13.,a=26.98*g/mole,density=2.7*g/cm3);


  //
  // ------------ Generate & Add Material Properties Table ------------
  //
    G4double WaterPhotonEnergy[] =
              { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
                2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
                2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
                2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
                2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
                3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
                3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
                3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };

    const G4int nEntries = sizeof(WaterPhotonEnergy)/sizeof(G4double);

  //
  // Water
  //
    G4double WaterRefractiveIndex1[] =
              { 1.3435, 1.344,  1.3445, 1.345,  1.3455,
                1.346,  1.3465, 1.347,  1.3475, 1.348,
                1.3485, 1.3492, 1.35,   1.3505, 1.351,
                1.3518, 1.3522, 1.3530, 1.3535, 1.354,
                1.3545, 1.355,  1.3555, 1.356,  1.3568,
                1.3572, 1.358,  1.3585, 1.359,  1.3595,
                1.36,   1.3608};

    assert(sizeof(WaterRefractiveIndex1) == sizeof(WaterPhotonEnergy));

    G4double WaterAbsorption[] =
             {3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
             15.152*m, 17.241*m, 18.868*m, 20.000*m, 26.316*m, 35.714*m,
             45.455*m, 47.619*m, 52.632*m, 52.632*m, 55.556*m, 52.632*m,
             52.632*m, 47.619*m, 45.455*m, 41.667*m, 37.037*m, 33.333*m,
             30.000*m, 28.500*m, 27.000*m, 24.500*m, 22.000*m, 19.500*m,
             17.500*m, 14.500*m };

    assert(sizeof(WaterAbsorption) == sizeof(WaterPhotonEnergy));

    G4MaterialPropertiesTable* WaterPropertiesTable = new G4MaterialPropertiesTable();

    WaterPropertiesTable->AddProperty("RINDEX",       WaterPhotonEnergy, WaterRefractiveIndex1,nEntries)
          ->SetSpline(true);
    WaterPropertiesTable->AddProperty("ABSLENGTH",    WaterPhotonEnergy, WaterAbsorption,     nEntries)
          ->SetSpline(true);


    G4double energy_water[] = {
       1.56962*eV, 1.58974*eV, 1.61039*eV, 1.63157*eV,
       1.65333*eV, 1.67567*eV, 1.69863*eV, 1.72222*eV,
       1.74647*eV, 1.77142*eV, 1.7971 *eV, 1.82352*eV,
       1.85074*eV, 1.87878*eV, 1.90769*eV, 1.93749*eV,
       1.96825*eV, 1.99999*eV, 2.03278*eV, 2.06666*eV,
       2.10169*eV, 2.13793*eV, 2.17543*eV, 2.21428*eV,
       2.25454*eV, 2.29629*eV, 2.33962*eV, 2.38461*eV,
       2.43137*eV, 2.47999*eV, 2.53061*eV, 2.58333*eV,
       2.63829*eV, 2.69565*eV, 2.75555*eV, 2.81817*eV,
       2.88371*eV, 2.95237*eV, 3.02438*eV, 3.09999*eV,
       3.17948*eV, 3.26315*eV, 3.35134*eV, 3.44444*eV,
       3.54285*eV, 3.64705*eV, 3.75757*eV, 3.87499*eV,
       3.99999*eV, 4.13332*eV, 4.27585*eV, 4.42856*eV,
       4.59258*eV, 4.76922*eV, 4.95999*eV, 5.16665*eV,
       5.39129*eV, 5.63635*eV, 5.90475*eV, 6.19998*eV
    };

    const G4int numentries_water = sizeof(energy_water)/sizeof(G4double);

    //assume 100 times larger than the rayleigh scattering for now.
    G4double mie_water[] = {
       167024.4*m, 158726.7*m, 150742  *m,
       143062.5*m, 135680.2*m, 128587.4*m,
       121776.3*m, 115239.5*m, 108969.5*m,
       102958.8*m, 97200.35*m, 91686.86*m,
       86411.33*m, 81366.79*m, 76546.42*m,
       71943.46*m, 67551.29*m, 63363.36*m,
       59373.25*m, 55574.61*m, 51961.24*m,
       48527.00*m, 45265.87*m, 42171.94*m,
       39239.39*m, 36462.50*m, 33835.68*m,
       31353.41*m, 29010.30*m, 26801.03*m,
       24720.42*m, 22763.36*m, 20924.88*m,
       19200.07*m, 17584.16*m, 16072.45*m,
       14660.38*m, 13343.46*m, 12117.33*m,
       10977.70*m, 9920.416*m, 8941.407*m,
       8036.711*m, 7202.470*m, 6434.927*m,
       5730.429*m, 5085.425*m, 4496.467*m,
       3960.210*m, 3473.413*m, 3032.937*m,
       2635.746*m, 2278.907*m, 1959.588*m,
       1675.064*m, 1422.710*m, 1200.004*m,
       1004.528*m, 833.9666*m, 686.1063*m
    };

    assert(sizeof(mie_water) == sizeof(energy_water));

    // gforward, gbackward, forward backward ratio
    G4double mie_water_const[3]={0.99,0.99,0.8};

    WaterPropertiesTable->AddProperty("MIEHG",energy_water,mie_water,numentries_water)
          ->SetSpline(true);
    WaterPropertiesTable->AddConstProperty("MIEHG_FORWARD",mie_water_const[0]);
    WaterPropertiesTable->AddConstProperty("MIEHG_BACKWARD",mie_water_const[1]);
    WaterPropertiesTable->AddConstProperty("MIEHG_FORWARD_RATIO",mie_water_const[2]);

    //G4cout << "Water G4MaterialPropertiesTable" << G4endl;
    //WaterPropertiesTable->DumpTable();

    water->SetMaterialPropertiesTable(WaterPropertiesTable);
 //=====================================

	//
	// Glass
	//

    G4double GlassPhotonEnergy[] =
              { 1.890*eV, 2.105*eV, 2.551*eV, 2.952*eV,
                4.136*eV };

    const G4int nGlassEntries = sizeof(GlassPhotonEnergy)/sizeof(G4double);

	  G4double GlassRefractiveIndex[] =
				{ 1.4705, 1.4727, 1.4776, 1.4800, 1.500};

	  assert(sizeof(GlassRefractiveIndex) == sizeof(GlassPhotonEnergy));

	  G4double GlassAbsorption[] =
			   {3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m };

	  assert(sizeof(GlassAbsorption) == sizeof(GlassPhotonEnergy));

	  G4MaterialPropertiesTable* GlassPropertiesTable = new G4MaterialPropertiesTable();

	  GlassPropertiesTable->AddProperty("RINDEX",       GlassPhotonEnergy, GlassRefractiveIndex,nGlassEntries)
			->SetSpline(true);
	  GlassPropertiesTable->AddProperty("ABSLENGTH",    GlassPhotonEnergy, GlassAbsorption,     nGlassEntries)
			->SetSpline(true);


	  glass->SetMaterialPropertiesTable(GlassPropertiesTable);



//=====================================



   //
   // Volumes definitions
   //



  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = false;

  //
  // World: WaterCube acts as world
  //

  G4Box* solid_WorldCube=
    new G4Box("WorldCube_solid",                       						//its name
    		WorldCube_SizeHalf, WorldCube_SizeHalf, WorldCube_SizeHalf);     	//its size

  G4LogicalVolume* logic_WorldCube =
    new G4LogicalVolume(solid_WorldCube,          							//its solid
                        air,           									//its material
                        "WorldCube_logic");    								//its name

  G4VPhysicalVolume* physical_WorldCube =
    new G4PVPlacement(0,                 								    //no rotation
                      G4ThreeVector(),       								//at (0,0,0)
                      logic_WorldCube,			          					//its logical volume
                      "WorldCube_physical",               					//its name
                      0,                     								//its mother  volume
                      false,                 								//no boolean operation
                      0,                     								//copy number
                      checkOverlaps);        								//overlaps checking

  // The Tyvek tube
  //
	G4Tubs* solid_TyvekTube
		= new G4Tubs (	"TyvekTube_solid" , //its name
			TyvekTube_innerRadious ,
			TyvekTube_outerRadious ,
			TyvekTube_halfHeight ,
			TyvekTube_startAngle ,
			TyvekTube_spannAngle ) ;

	G4LogicalVolume* logic_TyvekTube
	= new G4LogicalVolume ( solid_TyvekTube ,
		tyvek ,
		"TyvekTube_logic" ) ;

	G4VPhysicalVolume* physical_TyvekTube
	= new G4PVPlacement(0,
		G4ThreeVector(),
		logic_TyvekTube,
		"TyvekTube_physical",
		logic_WorldCube,
		false,
		0,
		checkOverlaps);

	// The Water tube
	//
	G4Tubs* solid_WaterTube
		= new G4Tubs (	"WaterTube_solid" , //its name
			WaterTube_innerRadious ,
			WaterTube_outerRadious ,
			WaterTube_halfHeight ,
			WaterTube_startAngle ,
			WaterTube_spannAngle ) ;

	G4LogicalVolume* logic_WaterTube
		= new G4LogicalVolume ( solid_WaterTube ,
			water ,
			"WaterTube_logic" ) ;

	G4VPhysicalVolume* physical_WaterTube
		= new G4PVPlacement(0,
			G4ThreeVector(),
			logic_WaterTube,
			"WaterTube_physical",
			logic_TyvekTube,
			false,
			0,
			checkOverlaps);




  //
  // PMT
  //
	// Glass sphere
	G4Sphere* solid_GlassSemiSphere =
		new G4Sphere( "GlassSemiSphere_solid",
				innerRadius,
				GlassSemiSphere_outerRadius,
				startPhiAngle,
				deltaPhiAngle,
				startThetaAngle,
				deltaThetaAngle);

	G4LogicalVolume* logic_GlassSemiSphere =
		new G4LogicalVolume( 	solid_GlassSemiSphere,
			glass,
			"GlassSemiSphere_logic");

	//  G4VPhysicalVolume* physical_GlassSphere =
		new G4PVPlacement(	0,
			G4ThreeVector(0.0*cm,0.0*cm,30.0*cm),
			logic_GlassSemiSphere,
			"GlassSemiSphere_physical",
			logic_WaterTube,
			false,
			0,
			checkOverlaps);


	// Metal sphere
	G4Sphere* solid_MetalSemiSphere =
		new G4Sphere( "MetalSemiSphere_solid",
				innerRadius,
				MetalSemiSphere_outerRadius,
				startPhiAngle,
				deltaPhiAngle,
				startThetaAngle,
				deltaThetaAngle);

	G4LogicalVolume* logic_MetalSemiSphere =
		new G4LogicalVolume( 	solid_MetalSemiSphere,
			aluminium,
			"MetalSemiSphere_logic");

	//  G4VPhysicalVolume* physical_MetalSphere =
		new G4PVPlacement(	0,
			G4ThreeVector( 0, 0, 0),
			logic_MetalSemiSphere,
			"MetalSemiSphere_physical",
			logic_GlassSemiSphere,
			false,
			0,
			checkOverlaps);


	// Vacuum sphere
	G4Sphere* solid_VacuumSemiSphere =
		new G4Sphere( "VacuumSemiSphere_solid",
				innerRadius,
				VacuumSemiSphere_outerRadius,
				startPhiAngle,
				deltaPhiAngle,
				startThetaAngle,
				deltaThetaAngle);

	G4LogicalVolume* logic_VacuumSemiSphere =
		new G4LogicalVolume( 	solid_VacuumSemiSphere,
			vacuum,
			"VacuumSemiSphere_logic");

	//  G4VPhysicalVolume* physical_VacuumSphere =
		new G4PVPlacement(	0,
			G4ThreeVector( 0, 0, 0),
			logic_VacuumSemiSphere,
			"VacuumSemiSphere_physical",
			logic_MetalSemiSphere,
			false,
			0,
			checkOverlaps);

  // Surfaces
  //
  // Tyvek
  //
    G4OpticalSurface* WaterSurface = new G4OpticalSurface("WaterSurface");
    WaterSurface->SetType(dielectric_metal);
    WaterSurface->SetFinish(ground);
    WaterSurface->SetModel(unified);


    new G4LogicalBorderSurface("WaterSurface", physical_WaterTube, physical_TyvekTube, WaterSurface);

    G4double pp[] = {2.0*eV, 3.5*eV};
    const G4int num_0 = sizeof(pp)/sizeof(G4double);
    G4double reflectivity[] = {0.9, 0.9};
    assert(sizeof(reflectivity) == sizeof(pp));
    G4double efficiency[] = {0.0, 0.0};
    assert(sizeof(efficiency) == sizeof(pp));

    G4MaterialPropertiesTable* WaterSurfaceProperty
      	  = new G4MaterialPropertiesTable();

    WaterSurfaceProperty->AddProperty("REFLECTIVITY",pp,reflectivity,num_0);
    WaterSurfaceProperty->AddProperty("EFFICIENCY",pp,efficiency,num_0);
    WaterSurface->SetMaterialPropertiesTable(WaterSurfaceProperty);

    //**Photocathode surface properties
//    G4double PhotonsEfficiencyEnergies[] = { 2.07*eV, 2.78*eV, 3.10*eV, 4.13*eV };
//    const G4int num_1 = sizeof( PhotonsEfficiencyEnergies ) / sizeof( G4double );
//    G4double photocath_EFF[]={ 1., 1., 1., 1. }; //Enables 'detection' of photons
//    G4double photocath_EFF[]={ 0.00103, 0.1218, 0.2418, 0.00827 }; //Enables 'detection' of photons
//	assert(sizeof(photocath_EFF) == sizeof( PhotonsEfficiencyEnergies ));
    G4double photocath_EFF[]={ 1.0, 1.0 }; //Enables 'detection' of photons
	assert(sizeof(photocath_EFF) == sizeof( pp ));
	G4double photocath_ReR[]={1.92,1.92};
	assert(sizeof(photocath_ReR) == sizeof(pp));
	G4double photocath_ImR[]={1.69,1.69};
	assert(sizeof(photocath_ImR) == sizeof(pp));
	G4MaterialPropertiesTable* photocath_mt = new G4MaterialPropertiesTable();
//	photocath_mt->AddProperty("EFFICIENCY",PhotonsEfficiencyEnergies,photocath_EFF,num_1);
	photocath_mt->AddProperty("EFFICIENCY",pp,photocath_EFF,num_0);
	photocath_mt->AddProperty("REALRINDEX",pp,photocath_ReR,num_0);
	photocath_mt->AddProperty("IMAGINARYRINDEX",pp,photocath_ImR,num_0);
	G4OpticalSurface* photocath_opsurf=
		new G4OpticalSurface("photocath_opsurf",glisur,polished,
							 dielectric_metal);
	photocath_opsurf->SetMaterialPropertiesTable(photocath_mt);
//	photocath_mt->DumpTable();
//	photocath_opsurf->DumpInfo();

      //**Create logical skin surfaces
        new G4LogicalSkinSurface("photocath_surf",logic_MetalSemiSphere,photocath_opsurf);


    // Set MetalSemiSphere as sensitive volume

    SensitiveVolume = logic_MetalSemiSphere;

	// Set WaterCube as scoring volume
	//
	ScoringVolume = logic_WaterTube;

  //
  //always return the physical World
  //
  return physical_WorldCube;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WCDtankDetectorConstruction::ConstructSDandField() {

  if (!SensitiveVolume) return;

  // PMT SD

  //G4cout << "Constructing Sensitive Detector" << G4endl;

  WCDtankSensitiveDetector* WCDtankSD = new WCDtankSensitiveDetector("/WCDtank/WCDtankSD");

  G4SDManager::GetSDMpointer()->AddNewDetector(WCDtankSD);

  SetSensitiveDetector(SensitiveVolume, WCDtankSD);

}
