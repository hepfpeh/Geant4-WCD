/*
 * elecRLCequivalent.hh
 *
 *  Created on: 13/10/2017
 *      Author: hepf
 */

#ifndef INCLUDE_ELECTRONICS_ELECRCEQUIVALENT_HH_
#define INCLUDE_ELECTRONICS_ELECRCEQUIVALENT_HH_

#include "elecTypes.hh"
#include "elecWCDtankPMTdata.hh"

class elecWCDtankPMTdata;


class elecRCequivalent {
public:
	elecRCequivalent(void);
	~elecRCequivalent(void);

	void PMTPulseVoltage(elecWCDtankPMTdata* PMTdata, elecDataTable* PMTPulseVoltageData);
	Double_t GetConst_k(void){ return Const_k; };

private:
// Circuit Parameters
	Double_t Circuit_R;
	Double_t Circuit_C;
	Double_t Circuit_V;
	Double_t Const_k;
};


#endif /* INCLUDE_ELECTRONICS_ELECRCEQUIVALENT_HH_ */
