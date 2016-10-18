//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "KinichAhauDetectorConstruction.hh"

#include "globals.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

KinichAhauDetectorConstruction::KinichAhauDetectorConstruction()
 : G4VUserDetectorConstruction()
{
  fExpHall_x = fExpHall_y = fExpHall_z = 1.0*m;
  fPhotocath_log = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

KinichAhauDetectorConstruction::~KinichAhauDetectorConstruction(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* KinichAhauDetectorConstruction::Construct()
{

// ------------- Materials -------------

  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* tyvek_mat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4double a, z, density;
  G4int nelements;

// Air
//
  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);

  G4Material* air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
  air->AddElement(N, 70.*perCent);
  air->AddElement(O, 30.*perCent);

// Water
//
  G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);

  G4Material* water = new G4Material("Water", density= 1.0*g/cm3, nelements=2);
  water->AddElement(H, 2);
  water->AddElement(O, 1);

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

  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();

  myMPT1->AddProperty("RINDEX",       photonEnergy, refractiveIndex1,nEntries)
        ->SetSpline(true);
  myMPT1->AddProperty("ABSLENGTH",    photonEnergy, absorption,     nEntries)
        ->SetSpline(true);

  G4cout << "Water G4MaterialPropertiesTable" << G4endl;
  myMPT1->DumpTable();

  water->SetMaterialPropertiesTable(myMPT1);

//
// Air
//
  G4double refractiveIndex2[] =
            { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00 };

  G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
  myMPT2->AddProperty("RINDEX", photonEnergy, refractiveIndex2, nEntries);

  G4cout << "Air G4MaterialPropertiesTable" << G4endl;
  myMPT2->DumpTable();

  air->SetMaterialPropertiesTable(myMPT2);

  //Aluminum
  G4Material* fAl = new G4Material("Al",z=13.,a=26.98*g/mole,density=2.7*g/cm3);

//
// ------------- Volumes --------------

//

G4bool checkOverlaps = true;

// The experimental Hall
//
  G4Box* expHall_box = new G4Box("World",fExpHall_x,fExpHall_y,fExpHall_z);

  G4LogicalVolume* expHall_log
    = new G4LogicalVolume(expHall_box,air,"World",0,0,0);

  G4VPhysicalVolume* expHall_phys
    = new G4PVPlacement(0,G4ThreeVector(),expHall_log,"World",0,false,0);

  // Rotacion
  G4ThreeVector pos1 = G4ThreeVector(0.*cm,0.*cm,0.*cm);
  G4RotationMatrix rotm  = G4RotationMatrix();
  rotm.rotateZ(90.*deg);
  G4Transform3D transform = G4Transform3D(rotm,pos1);

  // Tykev, cilindro
  G4double tyvek1_rmina =  0.*cm, tyvek1_rmaxa = 39.8*cm;
  G4double tyvek1_rminb =  0.*cm, tyvek1_rmaxb = 39.8*cm;
  G4double tyvek1_hz = 56.8*cm;
  G4double tyvek1_phimin = 0.*deg, tyvek1_phimax = 360.*deg;

  G4Cons* Tyvek_solid =
    new G4Cons("Tyvek_solid",
    tyvek1_rmina, tyvek1_rmaxa, tyvek1_rminb, tyvek1_rmaxb, tyvek1_hz,
    tyvek1_phimin, tyvek1_phimax);

  G4LogicalVolume* Tyvek_log =
    new G4LogicalVolume(Tyvek_solid, tyvek_mat, "Tyvek_log");

  G4VPhysicalVolume* Tyvek_phys =
    new G4PVPlacement(transform, Tyvek_log, "Tyvek_phys", expHall_log, false, 0, checkOverlaps);

  // The Water Tank

  G4double water1_rmina =  0.*cm, water1_rmaxa = 40.*cm;
  G4double water1_rminb =  0.*cm, water1_rmaxb = 40.*cm;
  G4double water1_hz = 57.*cm;
  G4double water1_phimin = 0.*deg, water1_phimax = 360.*deg;

  G4Cons* Water_solid =
    new G4Cons("Water",
    water1_rmina, water1_rmaxa, water1_rminb, water1_rmaxb, water1_hz,
    water1_phimin, water1_phimax);

  G4LogicalVolume* Water_log =
    new G4LogicalVolume(Water_solid,         //its solid
                        water,          //its material
                        "water_log");           //its name

  G4VPhysicalVolume* Water_phys =
	new G4PVPlacement(transform, Water_log, "Water_phys", Tyvek_log, false, 0, checkOverlaps);

  // Build PMTs
  G4double innerRadius_pmt = 0.*cm;
  G4double height_pmt = 5.*cm;
  G4double startAngle_pmt = 0.*deg;
  G4double spanningAngle_pmt = 360.*deg;
  G4double fOuterRadius_pmt = 10.*cm;

//  G4Tubs* fPmt = new G4Tubs("pmt_tube",innerRadius_pmt,fOuterRadius_pmt,
//                    height_pmt,startAngle_pmt,spanningAngle_pmt);

  //the "photocathode" is a metal slab at the back of the glass that
  //is only a very rough approximation of the real thing since it only
  //absorbs or detects the photons based on the efficiency set below
  G4Tubs* fPhotocath = new G4Tubs("photocath_tube",innerRadius_pmt,fOuterRadius_pmt,
                          height_pmt/2,startAngle_pmt,spanningAngle_pmt);

//  G4LogicalVolume* fPmt_log = new G4LogicalVolume(fPmt,G4Material::GetMaterial("Glass"),
//                                 "pmt_log");
  fPhotocath_log = new G4LogicalVolume(fPhotocath,
                                       fAl,
                                       "photocath_log");

  G4VPhysicalVolume * fPhotocath_phys = new G4PVPlacement(0,G4ThreeVector(0,0,-55.*cm),
                                    fPhotocath_log,"photocath",
                                    Water_log,false,0, checkOverlaps);

// ------------- Surfaces --------------
//
// Water Tank
//
  G4OpticalSurface* opWaterSurface = new G4OpticalSurface("WaterSurface");
  opWaterSurface->SetType(dielectric_metal);
  opWaterSurface->SetFinish(ground);
  opWaterSurface->SetModel(unified);

  new G4LogicalBorderSurface("waterSurface1", Water_phys,Tyvek_phys,opWaterSurface);

  const G4int num = 2;
  G4double ephoton[num] = {2.034*eV, 4.136*eV};

  // Water surface material properties table

  G4double reflectivity[num]       = {1.0, 1.0};
  G4double efficiency[num]         = {0.0, 0.0};
  G4double refractiveIndex[num] = {1.35, 1.40};
  G4double specularLobe[num]    = {0.3, 0.3};
  G4double specularSpike[num]   = {0.2, 0.2};
  G4double backScatter[num]     = {0.2, 0.2};

  G4MaterialPropertiesTable* WaterSurfaceMPT
  	  = new G4MaterialPropertiesTable();

  WaterSurfaceMPT->AddProperty("REFLECTIVITY",          ephoton, reflectivity,    num);
  WaterSurfaceMPT->AddProperty("EFFICIENCY",            ephoton, efficiency,      num);
  WaterSurfaceMPT->AddProperty("RINDEX",                ephoton, refractiveIndex, num);
  WaterSurfaceMPT->AddProperty("SPECULARLOBECONSTANT",  ephoton, specularLobe,    num);
  WaterSurfaceMPT->AddProperty("SPECULARSPIKECONSTANT", ephoton, specularSpike,   num);
  WaterSurfaceMPT->AddProperty("BACKSCATTERCONSTANT",   ephoton, backScatter,     num);

  G4cout << "Water Surface G4MaterialPropertiesTable" << G4endl;
  WaterSurfaceMPT->DumpTable();

  opWaterSurface->SetMaterialPropertiesTable(WaterSurfaceMPT);

  //OpticalAirSurface
  G4double reflectivity1[num] = {0.3, 0.5};
  G4double efficiency1[num]   = {0.0, 0.0};

  G4MaterialPropertiesTable *myST2 = new G4MaterialPropertiesTable();

  myST2->AddProperty("REFLECTIVITY", ephoton, reflectivity1, num);
  myST2->AddProperty("EFFICIENCY",   ephoton, efficiency1,   num);

  G4cout << "Air Surface G4MaterialPropertiesTable" << G4endl;
  myST2->DumpTable();

  //**Photocathode surface properties
  G4double photocath_EFF[]={0.9,0.9}; //Enables 'detection' of photons
  assert(sizeof(photocath_EFF) == sizeof(ephoton));
  G4double photocath_ReR[]={1.92,1.92};
  assert(sizeof(photocath_ReR) == sizeof(ephoton));
  G4double photocath_ImR[]={1.69,1.69};
  assert(sizeof(photocath_ImR) == sizeof(ephoton));
  G4MaterialPropertiesTable* photocath_mt = new G4MaterialPropertiesTable();
  photocath_mt->AddProperty("EFFICIENCY",ephoton,photocath_EFF,num);
  photocath_mt->AddProperty("REALRINDEX",ephoton,photocath_ReR,num);
  photocath_mt->AddProperty("IMAGINARYRINDEX",ephoton,photocath_ImR,num);
  G4OpticalSurface* photocath_opsurf=
    new G4OpticalSurface("photocath_opsurf",glisur,polished,
                         dielectric_metal);
  photocath_opsurf->SetMaterialPropertiesTable(photocath_mt);

  //**Create logical skin surfaces
  new G4LogicalSkinSurface("photocath_surf",fPhotocath_log,photocath_opsurf);

//always return the physical World
  return expHall_phys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void KinichAhauDetectorConstruction::ConstructSDandField() {

  if (!fPhotocath_log) return;

  // PMT SD

  KinichAhauSensitiveDetector* KinichAhauSD = new KinichAhauSensitiveDetector("/KinichAhau/KinichAhauSD");

  SetSensitiveDetector(fPhotocath_log, KinichAhauSD);

}
