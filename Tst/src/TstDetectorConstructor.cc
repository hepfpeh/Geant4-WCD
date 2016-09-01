#include "TstDetectorConstruction.hh"
#include "TstSensitiveDetector.hh"

#include "G4RunManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
//#include "G4Cons.hh"
#include "G4Orb.hh"
//#include "G4Sphere.hh"
//#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VSensitiveDetector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TstDetectorConstruction::TstDetectorConstruction()
: G4VUserDetectorConstruction()
{

	  // Water cube (world)
	  WaterCube_xSizeHalf	= 1.00*m;
	  WaterCube_ySizeHalf	= 1.00*m;
	  WaterCube_zSizeHalf	= 1.00*m;

	  // Tyvek foil
	  TyvekFoil_xSizeHalf	= 0.10*cm;
	  TyvekFoil_ySizeHalf	= 20.0*cm;
	  TyvekFoil_zSizeHalf	= 20.0*cm;

	  // PMT

	  // Glass sphere
	  GlassSphere_outerRadius		= 20.0*cm;

	  // Metal Sphere
	  MetalSphere_outerRadius		= 19.5*cm;

	  // Logical Volume

	  logic_MetalSphere = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TstDetectorConstruction::~TstDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* TstDetectorConstruction::Construct()
{

  // Some elements
  G4double a, z, density;
  G4int nelements;

  G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);

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
    G4double photonEnergy[] =
              { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
                2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
                2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
                2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
                2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
                3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
                3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
                3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };

    const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);

  //
  // Water
  //
    G4double refractiveIndex1[] =
              { 1.3435, 1.344,  1.3445, 1.345,  1.3455,
                1.346,  1.3465, 1.347,  1.3475, 1.348,
                1.3485, 1.3492, 1.35,   1.3505, 1.351,
                1.3518, 1.3522, 1.3530, 1.3535, 1.354,
                1.3545, 1.355,  1.3555, 1.356,  1.3568,
                1.3572, 1.358,  1.3585, 1.359,  1.3595,
                1.36,   1.3608};

    assert(sizeof(refractiveIndex1) == sizeof(photonEnergy));

    G4double absorption[] =
             {3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
             15.152*m, 17.241*m, 18.868*m, 20.000*m, 26.316*m, 35.714*m,
             45.455*m, 47.619*m, 52.632*m, 52.632*m, 55.556*m, 52.632*m,
             52.632*m, 47.619*m, 45.455*m, 41.667*m, 37.037*m, 33.333*m,
             30.000*m, 28.500*m, 27.000*m, 24.500*m, 22.000*m, 19.500*m,
             17.500*m, 14.500*m };

    assert(sizeof(absorption) == sizeof(photonEnergy));

    G4MaterialPropertiesTable* WaterPropertiesTable = new G4MaterialPropertiesTable();

    WaterPropertiesTable->AddProperty("RINDEX",       photonEnergy, refractiveIndex1,nEntries)
          ->SetSpline(true);
    WaterPropertiesTable->AddProperty("ABSLENGTH",    photonEnergy, absorption,     nEntries)
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


   //
   // Volumes definitions
   //



  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World: WaterCube acts as world
  //

  G4Box* solid_WaterCube=
    new G4Box("WaterCube_solid",                       						//its name
       WaterCube_xSizeHalf, WaterCube_ySizeHalf, WaterCube_zSizeHalf);     	//its size

  G4LogicalVolume* logic_WaterCube =
    new G4LogicalVolume(solid_WaterCube,          							//its solid
                        water,           									//its material
                        "WaterCube_logic");    								//its name

  G4VPhysicalVolume* physical_WaterCube =
    new G4PVPlacement(0,                 								    //no rotation
                      G4ThreeVector(),       								//at (0,0,0)
                      logic_WaterCube,			          					//its logical volume
                      "WaterCube_physical",               					//its name
                      0,                     								//its mother  volume
                      false,                 								//no boolean operation
                      0,                     								//copy number
                      checkOverlaps);        								//overlaps checking

  //
  // Tyvek Foil
  //
  G4Box* solid_TyvekFoil =
    new G4Box("TyvekFoil_solid",                    						//its name
        TyvekFoil_xSizeHalf, TyvekFoil_ySizeHalf, TyvekFoil_zSizeHalf); 	//its size

  G4LogicalVolume* logic_TyvekFoil =
    new G4LogicalVolume(solid_TyvekFoil,            						//its solid
                        tyvek,             									//its material
                        "TyvekFoil_logic");         						//its name

  G4VPhysicalVolume* physical_TyvekFoil =
	new G4PVPlacement(0,                       								//no rotation
                    G4ThreeVector(),         								//at (0,0,0)
                    logic_TyvekFoil,                						//its logical volume
                    "TyvekFoil_physical",              						//its name
                    logic_WaterCube,              							//its mother  volume
                    false,                   								//no boolean operation
                    0,                       								//copy number
                    checkOverlaps);          								//overlaps checking


  //
  // PMT
  //
  // Glass sphere
/*  G4Orb* solid_GlassSphere =
		  new G4Orb( "GlassSphere_solid", GlassSphere_outerRadius );

  G4LogicalVolume* logic_GlassSphere =
		  new G4LogicalVolume( 	solid_GlassSphere,
				  	  	  	  	glass,
								"GlassSphere_logic");

  G4VPhysicalVolume* physical_GlassSphere =
		  new G4PVPlacement(	0,
				  	  	  	G4ThreeVector(50.0*cm,50.0*cm,50.0*cm),
							logic_GlassSphere,
							"GlassSphere_physical",
							logic_WaterCube,
							false,
							0,
							checkOverlaps);
*/

  // Metal sphere
  G4Orb* solid_MetalSphere =
		  new G4Orb( "MetalSphere_solid", MetalSphere_outerRadius );

  logic_MetalSphere =
		  new G4LogicalVolume( 	solid_MetalSphere,
				  	  	  	  	aluminium,
								"MetalSphere_logic");

  G4VPhysicalVolume* physical_MetalSphere =
		  new G4PVPlacement(	0,
				  	  	  		G4ThreeVector(50.0*cm,50.0*cm,50.0*cm),
								logic_MetalSphere,
								"MetalSphere_physical",
								logic_WaterCube,
								false,
								0,
								checkOverlaps);

  // Surfaces
  //
  // Tyvek
  //
    G4OpticalSurface* TyvekSurface = new G4OpticalSurface("TyvekSurface");
    TyvekSurface->SetType(dielectric_metal);
    TyvekSurface->SetFinish(ground);
    TyvekSurface->SetModel(unified);


    new G4LogicalBorderSurface("TyvekSurface", physical_WaterCube, physical_TyvekFoil, TyvekSurface);

    G4double pp[] = {2.0*eV, 3.5*eV};
    const G4int num_0 = sizeof(pp)/sizeof(G4double);
    G4double reflectivity[] = {0.9, 0.9};
    assert(sizeof(reflectivity) == sizeof(pp));
    G4double efficiency[] = {0.0, 0.0};
    assert(sizeof(efficiency) == sizeof(pp));

    G4MaterialPropertiesTable* TyvekSurfaceProperty
      	  = new G4MaterialPropertiesTable();

    TyvekSurfaceProperty->AddProperty("REFLECTIVITY",pp,reflectivity,num_0);
    TyvekSurfaceProperty->AddProperty("EFFICIENCY",pp,efficiency,num_0);
    TyvekSurface->SetMaterialPropertiesTable(TyvekSurfaceProperty);

    //**Photocathode surface properties
      G4double photocath_EFF[]={1.,1.}; //Enables 'detection' of photons
      assert(sizeof(photocath_EFF) == sizeof(pp));
      G4double photocath_ReR[]={1.92,1.92};
      assert(sizeof(photocath_ReR) == sizeof(pp));
      G4double photocath_ImR[]={1.69,1.69};
      assert(sizeof(photocath_ImR) == sizeof(pp));
      G4MaterialPropertiesTable* photocath_mt = new G4MaterialPropertiesTable();
      photocath_mt->AddProperty("EFFICIENCY",pp,photocath_EFF,num_0);
      photocath_mt->AddProperty("REALRINDEX",pp,photocath_ReR,num_0);
      photocath_mt->AddProperty("IMAGINARYRINDEX",pp,photocath_ImR,num_0);
      G4OpticalSurface* photocath_opsurf=
        new G4OpticalSurface("photocath_opsurf",glisur,polished,
                             dielectric_metal);
      photocath_opsurf->SetMaterialPropertiesTable(photocath_mt);

      //**Create logical skin surfaces
        new G4LogicalSkinSurface("photocath_surf",logic_MetalSphere,photocath_opsurf);

  //
  //always return the physical World
  //
  return physical_WaterCube;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TstDetectorConstruction::ConstructSDandField() {

  if (!logic_MetalSphere) return;

  // PMT SD

  TstSensitiveDetector* TstSD = new TstSensitiveDetector("/Tst/TstSD");

  SetSensitiveDetector(logic_MetalSphere, TstSD);

}
