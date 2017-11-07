/*
*
*/

#include <elecCommandLine.hh>
#include <cstdlib>

elecCommandLine::elecCommandLine(int ArgCount, char** ArgVector){

	AddProgramDescription("Hunapu WCD electronics simulation");
/*
	AddOption("b_option", 'b', "Test option b. No arguments", optArgType::boolean);
	AddOption("s_option", 's', "Test option s. Argument is an string.", optArgType::string);
	AddOption("i_option", 'i', "Test option i. Argument is an integer", optArgType::integer);
	AddOption("f_option", 'f', "Test option f. Argument is a float", optArgType::floating);
*/
	AddGlobalArgument( "in_file", "Root input file name");
//	AddGlobalArgument( "second", "Second obligatory argument");

	if( !Parse( ArgCount, ArgVector ) ){
		PrintUsageMessage( ArgVector[0] );
		std::exit(1);
	}
}
