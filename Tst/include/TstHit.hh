/*
 * TstHit.hh
 *
 *  Created on: 5/09/2016
 *      Author: hepf
 */

#ifndef TSTHIT_HH_
#define TSTHIT_HH_

#include "G4VHit.hh"

class TstHit : public G4VHit
{
  public:

    TstHit();
    virtual ~TstHit();
    TstHit(const TstHit &right);

    const TstHit& operator=(const TstHit &right);

    inline void IncPhotonCount(){TstPhotonsPerEvent++;}
    inline G4int GetPhotonCount(){return TstPhotonsPerEvent;}

  private:

    G4int TstPhotonsPerEvent;

};


#endif /* TSTHIT_HH_ */
