/*
*
*/

#include "elecCommandLine.hh"
#include "elecWCDtankPMTdata.hh"
#include "elecRCequivalent.hh"
#include "elecADC.hh"


#include <vector>
#include <iostream>

int main(int argc, char **argv){

	elecCommandLine *myelecCommandLine = new elecCommandLine(argc, argv);
/*
	std::string s_option_value;
	if( myelecCommandLine->GetOptionValue( "s_option", s_option_value ) == 0 )
		std::cout << "s_option was set with value: " << s_option_value << std::endl;

	int i_option_value;
	if( myelecCommandLine->GetOptionValue( "i_option", i_option_value ) == 0 )
		std::cout << "i_option was set with value: " << i_option_value << std::endl;

	float f_option_value;
	if( myelecCommandLine->GetOptionValue( "f_option", f_option_value ) == 0 )
		std::cout << "f_option was set with value: " << f_option_value << std::endl;

	if( myelecCommandLine->GetOptionValue( "b_option" ) )
		std::cout << "b_option was set" << std::endl;
*/
	std::string HunapuRootFileName;
	if( myelecCommandLine->GetGlobalArgumentValue("in_file", HunapuRootFileName) == 0 )
		std::cout << "Root data file name: " << HunapuRootFileName << std::endl;
/*
	std::string second_garg_value;
	if( myelecCommandLine->GetGlobalArgumentValue("second", second_garg_value) == 0 )
		std::cout << "second global argument value: " << second_garg_value << std::endl;
*/

	elecWCDtankPMTdata* HunapuPMTData = new elecWCDtankPMTdata();

	HunapuPMTData->LoadRootFile( HunapuRootFileName.c_str () );

	elecRCequivalent *HunapuRCequivalentCircuit = new elecRCequivalent();
//
//	elecDataTable* HunapuPulsesVoltage = new elecDataTable();
//
//	HunapuRCequivalentCircuit->PMTPulseVoltage(HunapuPMTData, HunapuPulsesVoltage);
//
//	std::cout << "HunapuPulsesVoltage size: " << HunapuPulsesVoltage->size() << std::endl;

	elecADC* HunapuADC = new elecADC;

	HunapuADC->DigitalizeVoltagePulses(HunapuPMTData, HunapuRCequivalentCircuit, elecADCoutput::none);

//	char aChar;
//
//	std::cout << "Press any key and enter: " ;
//	std::cin >> aChar;
//	std::cout << std::endl;

	return 0;
}
