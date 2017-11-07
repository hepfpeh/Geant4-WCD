/*
 * elecADCsim.hh
 *
 *  Created on: 23/10/2017
 *      Author: hepf
 */

#ifndef INCLUDE_ELECTRONICS_ELECADC_HH_
#define INCLUDE_ELECTRONICS_ELECADC_HH_

#include "elecTypes.hh"
#include "elecRCequivalent.hh"
#include "elecWCDtankPMTdata.hh"


class elecWCDtankPMTdata;
class elecRCequivalent;

enum class elecADCoutput { file, histogram, none };

class elecADC {
public:
	elecADC(void);
	~elecADC(void);

	void DigitalizeVoltagePulses( elecWCDtankPMTdata* PMTPulsesData , elecRCequivalent* RCequivalentCircuit, elecADCoutput Output);

private:
	Int_t		ADC_bits;
	Double_t	ADC_Vref;
	Double_t	ADC_Sample_Rate;
	Int_t		ADC_Samples_per_Pulse;
	Double_t	ADC_Trigger_Voltaje;
	Int_t		ADC_Trigger_Sample_Offset;

};



#endif /* INCLUDE_ELECTRONICS_ELECADC_HH_ */
