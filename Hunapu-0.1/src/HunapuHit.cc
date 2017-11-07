/*
 * HunapuHit.cc
 *
 *  Created on: 5/09/2016
 *      Author: hepf
 */

#include "HunapuHit.hh"
#include "G4ios.hh"
#include "G4VVisManager.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

G4ThreadLocal G4Allocator<HunapuHit>* HunapuHitAllocator=0;

HunapuHit::HunapuHit()
  : HunapuPhotonsPerEvent(0),
	PhotonArrivalTime(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HunapuHit::~HunapuHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HunapuHit::HunapuHit(const HunapuHit &right) : G4VHit()
{
	HunapuPhotonsPerEvent	= right.HunapuPhotonsPerEvent;
	PhotonArrivalTime		= right.PhotonArrivalTime;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const HunapuHit& HunapuHit::operator=(const HunapuHit &right){
	HunapuPhotonsPerEvent	= right.HunapuPhotonsPerEvent;
	PhotonArrivalTime		= right.PhotonArrivalTime;
  return *this;
}



