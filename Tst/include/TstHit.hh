/*
 * TstHit.hh
 *
 *  Created on: 5/09/2016
 *      Author: hepf
 */

#ifndef TSTHIT_HH_
#define TSTHIT_HH_

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class TstHit : public G4VHit
{
  public:

    TstHit();
    virtual ~TstHit();
    TstHit(const TstHit &right);

    const TstHit& operator=(const TstHit &right);

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    inline void IncPhotonCount(){TstPhotonsPerEvent++;}
    inline G4int GetPhotonCount(){return TstPhotonsPerEvent;}
    inline void ResetPhotonCount(){TstPhotonsPerEvent=0;}

  private:

    G4int TstPhotonsPerEvent;

};

typedef G4THitsCollection<TstHit> TstHitsCollection;

extern G4ThreadLocal G4Allocator<TstHit>* TstHitAllocator;

inline void* TstHit::operator new(size_t){
  if(!TstHitAllocator)
      TstHitAllocator = new G4Allocator<TstHit>;
  return (void *) TstHitAllocator->MallocSingle();
}

inline void TstHit::operator delete(void *aHit){
  TstHitAllocator->FreeSingle((TstHit*) aHit);
}

#endif /* TSTHIT_HH_ */
