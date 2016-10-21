/*
 * HunapuHit.hh
 *
 *  Created on: 5/09/2016
 *      Author: hepf
 */

#ifndef HunapuHIT_HH_
#define HunapuHIT_HH_

#include <vector>

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class HunapuHit : public G4VHit
{
  public:

    HunapuHit();
    virtual ~HunapuHit();
    HunapuHit(const HunapuHit &right);

    const HunapuHit& operator=(const HunapuHit &right);

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    inline void IncPhotonCount(){HunapuPhotonsPerEvent++;}
    inline void AddPhotonTime( G4double Time ){PhotonArrivalTime->push_back( Time );}
    inline void SetPhotonTime( std::vector<G4double>* aVector ){ PhotonArrivalTime = aVector;}
    inline G4int GetPhotonCount(){return HunapuPhotonsPerEvent;}
    inline G4int GetPhotonTimeSize(){return PhotonArrivalTime->size();}
    inline void ResetPhotonCount(){HunapuPhotonsPerEvent=0;}
    inline void ResetPhotonTime(){PhotonArrivalTime->clear();}

  private:

    G4int 					HunapuPhotonsPerEvent;
    std::vector<G4double>	*PhotonArrivalTime;

};

typedef G4THitsCollection<HunapuHit> HunapuHitsCollection;

extern G4ThreadLocal G4Allocator<HunapuHit>* HunapuHitAllocator;

inline void* HunapuHit::operator new(size_t){
  if(!HunapuHitAllocator)
      HunapuHitAllocator = new G4Allocator<HunapuHit>;
  return (void *) HunapuHitAllocator->MallocSingle();
}

inline void HunapuHit::operator delete(void *aHit){
  HunapuHitAllocator->FreeSingle((HunapuHit*) aHit);
}

#endif /* HunapuHIT_HH_ */
