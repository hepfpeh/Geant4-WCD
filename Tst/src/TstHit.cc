/*
 * TstHit.cc
 *
 *  Created on: 5/09/2016
 *      Author: hepf
 */

#include "TstHit.hh"
#include "G4ios.hh"
#include "G4VVisManager.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

G4ThreadLocal G4Allocator<TstHit>* TstHitAllocator=0;

TstHit::TstHit()
  : TstPhotonsPerEvent(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TstHit::~TstHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TstHit::TstHit(const TstHit &right) : G4VHit()
{
	TstPhotonsPerEvent=right.TstPhotonsPerEvent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const TstHit& TstHit::operator=(const TstHit &right){
	TstPhotonsPerEvent=right.TstPhotonsPerEvent;
  return *this;
}



