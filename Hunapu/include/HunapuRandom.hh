/*
 * HunapuRandom.h
 *
 *  Created on: 12/10/2016
 *      Author: hepf
 */

#ifndef HUNAPURANDOM_HH_
#define HUNAPURANDOM_HH_

#include "G4PhysicalConstants.hh"

#include "Randomize.hh"
#include "globals.hh"

#include <cmath>

G4double CosSqrDistRand(){

	G4double x = G4UniformRand() * halfpi;
	G4double y = G4UniformRand();

	while( y > (std::cos(x))*(std::cos(x)) )
	{
		x = G4UniformRand() * halfpi;
		y = G4UniformRand();
	}

	return x;

}

#endif /* HUNAPURANDOM_HH_ */
