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

#include "OpNoviceDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4Sphere.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSTrackLength.hh"
#include "G4PSNofStep.hh"
#include "G4SDParticleFilter.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceDetectorConstruction::OpNoviceDetectorConstruction()
 : G4VUserDetectorConstruction(), flogicTubo3(0)
{
  fExpHall_x = fExpHall_y = fExpHall_z = 0.75*m;
  fTank_x    = fTank_y    = fTank_z    =  5.0*m;
  fBubble_x  = fBubble_y  = fBubble_z  =  0.5*m;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceDetectorConstruction::~OpNoviceDetectorConstruction(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* OpNoviceDetectorConstruction::Construct()
{

// ------------- Materials -------------

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

//tyvek
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* tyvek = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

//sphere glass
G4Material* pmt_mat1 = nist->FindOrBuildMaterial("G4_Pyrex_Glass");

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


  myMPT1->AddConstProperty("SCINTILLATIONYIELD",50./MeV);
  myMPT1->AddConstProperty("RESOLUTIONSCALE",1.0);

  G4cout << "Water G4MaterialPropertiesTable" << G4endl;
  myMPT1->DumpTable();

  water->SetMaterialPropertiesTable(myMPT1);


// ------------- Volumes --------------

// The experimental Hall
//
  G4Box* expHall_box = new G4Box("World",fExpHall_x,fExpHall_y,fExpHall_z);

  G4LogicalVolume* expHall_log
    = new G4LogicalVolume(expHall_box,air,"World",0,0,0);

  G4VPhysicalVolume* expHall_phys
    = new G4PVPlacement(0,G4ThreeVector(),expHall_log,"World",0,false,0);

// The tyvek Tank
//


 G4bool checkOverlaps = true;
  G4double Tubo1_innerR  = 0.*cm;
  G4double Tubo1_outerR  = 25.1*cm;
  G4double Tubo1_height = 45.475*cm;
  G4double Tubo1_startAngle = 0.*deg;
  G4double Tubo1_spanningAngle = 360.*deg;

 G4Tubs* solidtubo1 = 
    new G4Tubs ( "Tubo1" , //its name
                Tubo1_innerR , Tubo1_outerR ,Tubo1_height, Tubo1_startAngle , 
                Tubo1_spanningAngle ) ; //its size

  G4LogicalVolume* logicTubo1 =
    new G4LogicalVolume ( solidtubo1 , //its solid
                          tyvek,  //its material
                       " Tubo1_log " ) ; //its name
                                   
  G4VPhysicalVolume* physTubo1 = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicTubo1,            //its logical volume
                      "Tubo1",               //its name
                      expHall_log,           //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

//The Water Tank

  G4double Tubo2_innerR  = 0.*cm;
  G4double Tubo2_outerR  = 25.07*cm;
  G4double Tubo2_height = 45.445*cm;
  G4double Tubo2_startAngle = 0.*deg;
  G4double Tubo2_spanningAngle = 360.*deg;

 G4Tubs* solidtubo2 = 
    new G4Tubs ( "Tubo2" , //its name
                Tubo2_innerR , Tubo2_outerR ,Tubo2_height, Tubo2_startAngle , 
                Tubo2_spanningAngle ) ; //its size

  G4LogicalVolume* logicTubo2 =
    new G4LogicalVolume ( solidtubo2 , //its solid
                          water,  //its material
                       " Tubo2_log " ) ; //its name
                                   
  G4VPhysicalVolume* physTubo2 = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicTubo2,            //its logical volume
                      "Tubo2",               //its name
                      logicTubo1,           //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

//The PMT cover Sphere Glass

G4double  pRmin=10.61*cm;
G4double  pRmax=10.65*cm;
G4double  pSPhi=0.*deg;
G4double  pDPhi=180.*deg;
G4double  pSTheta=0.*deg;
G4double  pDTheta=180.*deg;

  G4Sphere* glass_pmt= new G4Sphere("Sphere",
             			     pRmin,
                                     pRmax,
                                     pSPhi,
                                     pDPhi,
                                     pSTheta,
                                     pDTheta);


  G4LogicalVolume* glass_logic_pmt =
    new G4LogicalVolume ( glass_pmt , //its solid
                          pmt_mat1 ,  //its material
                         "Sphere_log") ; //its name

 G4RotationMatrix *rm=new G4RotationMatrix;
 rm->rotateX(-90*deg);
    new G4PVPlacement(rm,                     //rotation
                      G4ThreeVector(0,0,-45.475*cm),       
                      glass_logic_pmt,            //its logical volume
                      "pmt",               //its name
                      logicTubo2,             //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking


//Fotcatodo.

  G4double foto_x = 5.0*cm;
  G4double foto_y = 5.0*cm;
  G4double foto_z = 0.5*cm;
  G4Material* pmt_mat2 = nist->FindOrBuildMaterial("G4_Al");
  
  G4Box* solidtubo3 =    
    new G4Box("Tubo3",                       //its name
       foto_x,foto_y,foto_z);     //its size
      
  flogicTubo3 =                         
    new G4LogicalVolume(solidtubo3,          //its solid
                        pmt_mat2,           //its material
                        "Tubo_log");            //its name
 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(0,0,-43.*cm),       //at (0,0,0)
                      flogicTubo3,            //its logical volume
                      "Tubo3",               //its name
                      logicTubo2,       //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking




// ------------- Surfaces --------------
//Between tyvek and water tanks

    G4OpticalSurface* TyvekSurface = new G4OpticalSurface("TyvekSurface");
    TyvekSurface->SetType(dielectric_metal);
    TyvekSurface->SetFinish(ground);
    TyvekSurface->SetModel(unified);


    new G4LogicalBorderSurface("TyvekSurface", physTubo2, physTubo1, TyvekSurface);

    G4double pp[] = {2.0*eV, 4.0*eV};
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


//always return the physical World
  return expHall_phys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
