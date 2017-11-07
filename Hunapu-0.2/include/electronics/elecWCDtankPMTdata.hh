/*
 * elecWCDtankPMTdata.hh
 *
 *  Created on: 12/10/2017
 *      Author: hepf
 */

#ifndef INCLUDE_ELECWCDTANKPMTDATA_HH_
#define INCLUDE_ELECWCDTANKPMTDATA_HH_

#include "elecTypes.hh"

#include "TTree.h"
#include "TFile.h"

class TFile;
class TTree;

class elecWCDtankPMTdata {
public:
	elecWCDtankPMTdata(void);
	~elecWCDtankPMTdata(void);

	void LoadRootFile( const char* RootFileName);

	Long64_t GetNumberOfPulses(void){ return Entries; };

	void					SetPulse 			( Long64_t PulseNumber = 0 );
	Int_t 					GetPulseOrientation ( void );
	std::vector<G4double>* 	GetPulseTimeData	( void );


private:
	TTree*	 				PMTdata;
	Long64_t 				Entries;

	Double_t 				Primary_Energy;
	Double_t 				Cenit_angle;
	Int_t 					Direction;
	Double_t 				Deposited_Energy;
	Double_t 				Track_Length;
	Double_t 				Photon_Count;
	std::vector<Double_t>*	PulseTimeData;
};



#endif /* INCLUDE_ELECWCDTANKPMTDATA_HH_ */
