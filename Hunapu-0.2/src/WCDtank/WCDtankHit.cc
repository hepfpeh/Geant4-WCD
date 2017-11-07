/*
 * WCDtankHit.cc
 *
 *  Created on: 5/09/2016
 *      Author: hepf
 */

#include "WCDtankHit.hh"
#include "G4ios.hh"
#include "G4VVisManager.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

G4ThreadLocal G4Allocator<WCDtankHit>* WCDtankHitAllocator=0;

WCDtankHit::WCDtankHit()
{
	WCDtankPhotonsPerEvent = 0;
//	PhotonArrivalTime = new std::vector<G4double>;
	PhotonArrivalTime = 0;
//	G4cout << "WCDtankHit()" << G4endl;
//	G4cout << "WCDtankHit: "<<  (void *)this << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WCDtankHit::~WCDtankHit()
{
//	G4cout << "\n~WCDtankHit()" << G4endl;
//	G4cout << "PhotonArrivalTime: "<<  (void *)PhotonArrivalTime << G4endl;
//	G4cout << "PhotonArrivalTime->size(): "<<  PhotonArrivalTime->size() << G4endl;
//	G4cout << "~WCDtankHit: "<<  (void *)this << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WCDtankHit::WCDtankHit(const WCDtankHit &right) : G4VHit()
{
	WCDtankPhotonsPerEvent	= right.WCDtankPhotonsPerEvent;
	PhotonArrivalTime		= right.PhotonArrivalTime;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const WCDtankHit& WCDtankHit::operator=(const WCDtankHit &right){
	WCDtankPhotonsPerEvent	= right.WCDtankPhotonsPerEvent;
	PhotonArrivalTime		= right.PhotonArrivalTime;
  return *this;
}



