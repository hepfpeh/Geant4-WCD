/*
 * elecWCDtankPMTdata.cc
 *
 *  Created on: 12/10/2017
 *      Author: hepf
 */

#include "elecWCDtankPMTdata.hh"

// C

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

// Root

#include "TFile.h"
#include "TTree.h"
#include "Rtypes.h"

// Geant4

#include "globals.hh"

elecWCDtankPMTdata::elecWCDtankPMTdata(void)
{
	PMTdata				= 0;
	Entries				= -1;

	Primary_Energy		= -1;
	Cenit_angle			= -1;
	Direction			= -1;
	Deposited_Energy	= -1;
	Track_Length		= -1;
	Photon_Count		= -1;
	PulseTimeData		= 0;
}

elecWCDtankPMTdata::~elecWCDtankPMTdata(void)
{}

void elecWCDtankPMTdata::LoadRootFile( const char* RootFileName)
{
	TFile *RootFile = new TFile( RootFileName );
	PMTdata = (TTree*)RootFile->Get("WCDtank;1");
	Entries = PMTdata->GetEntriesFast();
}

void elecWCDtankPMTdata::SetPulse( Long64_t PulseNumber )
{
	if( !PulseTimeData )
		PulseTimeData = new std::vector < Double_t >;

//	Double_t tmp = 0;

	PMTdata->SetBranchAddress("Primary_Energy",		&Primary_Energy);
	PMTdata->SetBranchAddress("Azimuth_angle",		&Cenit_angle);
	PMTdata->SetBranchAddress("Direction",			&Direction);
//	PMTdata->SetBranchAddress("Direction",			&tmp);
	PMTdata->SetBranchAddress("Deposited_Energy",	&Deposited_Energy);
	PMTdata->SetBranchAddress("Track_Length",		&Track_Length);
	PMTdata->SetBranchAddress("Photon_Count",		&Photon_Count);
	PMTdata->SetBranchAddress("Photon_Arrival_Time",&PulseTimeData);


	if (PulseNumber < Entries ) PMTdata->GetEntry(PulseNumber);
	else {
		std::cout << "Invalid pulse Number" << std::endl;
		return;
	}

//	Direction = (int)tmp;
	std::sort( PulseTimeData->begin(), PulseTimeData->end() );
}

std::vector< Double_t >* elecWCDtankPMTdata::GetPulseTimeData( void )
{
	return PulseTimeData;
}

Int_t elecWCDtankPMTdata::GetPulseOrientation( void )
{
	return Direction;
}
