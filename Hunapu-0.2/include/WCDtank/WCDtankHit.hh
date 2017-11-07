/*
 * WCDtankHit.hh
 *
 *  Created on: 5/09/2016
 *      Author: hepf
 */

#ifndef WCDtankHIT_HH_
#define WCDtankHIT_HH_

#include <vector>

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class WCDtankHit : public G4VHit
{
  public:

    WCDtankHit();
    virtual ~WCDtankHit();
    WCDtankHit(const WCDtankHit &right);

    const WCDtankHit& operator=(const WCDtankHit &right);

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    inline void IncPhotonCount(){WCDtankPhotonsPerEvent++;}
    inline void AddPhotonTime( G4double Time ){PhotonArrivalTime->push_back( Time );}
    inline void SetPhotonTime( std::vector<G4double>* aVector ){ PhotonArrivalTime = aVector;}
    inline G4int GetPhotonCount(){return WCDtankPhotonsPerEvent;}
    inline G4int GetPhotonTimeSize(){return PhotonArrivalTime->size();}
    inline std::vector<G4double>* GetPhotonTime(){return PhotonArrivalTime;}
    inline void ResetPhotonCount(){WCDtankPhotonsPerEvent=0;}
    inline void ResetPhotonTime(){PhotonArrivalTime->clear();}

  private:

    G4int 					WCDtankPhotonsPerEvent;
    std::vector<G4double>	*PhotonArrivalTime;

};

typedef G4THitsCollection<WCDtankHit> WCDtankHitsCollection;

extern G4ThreadLocal G4Allocator<WCDtankHit>* WCDtankHitAllocator;


inline void* WCDtankHit::operator new(size_t){
  if(!WCDtankHitAllocator)
      WCDtankHitAllocator = new G4Allocator<WCDtankHit>;
  return (void *) WCDtankHitAllocator->MallocSingle();
}

inline void WCDtankHit::operator delete(void *aHit){
  WCDtankHitAllocator->FreeSingle((WCDtankHit*) aHit);
}

#endif /* WCDtankHIT_HH_ */
