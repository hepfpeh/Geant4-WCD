/*
* clap.cc
*/

#include "CLAcmdln.hh"
#include "CLAtdopt.hh"
#include "CLAdglbarg.hh"
#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>

CLAcommandLine::CLAcommandLine(uint8_t verbousity){
	gargCount = 0;
	verb = verbousity;
}

int CLAcommandLine::AddOption(std::string optionName, char optionChar, std::string optionDescription, optArgType optionArgumentType){
	if ( !FindOption(optionName) && !FindOption(optionChar)){
		CLAtdoption newOption(optionName, optionChar, optionDescription, optionArgumentType);
		optionList.push_back(newOption);
		return 0;
	}
	std::cerr << "Option name or char can not be duplicated." << std::endl;
	exit(1);
}

bool CLAcommandLine::FindOption(char optionChar){
	uint8_t i = 0;
	bool isPresent = false;
	while( (i < optionList.size()) && (!isPresent) ){
		if( optionList[i].GetOptionChar() == optionChar )
			isPresent = true;
		i++;
	}
	return isPresent;
}

bool CLAcommandLine::FindOption(std::string optionName){
	uint8_t i = 0;
	bool isPresent = false;
	while( (i < optionList.size()) && (!isPresent) ){
		if( optionName.compare( optionList[i].GetOptionName() ) == 0 )
			isPresent = true;
		i++;
	}
	return isPresent;
}

int CLAcommandLine::SetOptionValue(char optionChar){
	uint8_t i = 0;
	bool optionFound = false;
	bool optionAlreadySet =false;
	bool optionIsBoolean = true;
	while( (i < optionList.size()) && (!optionFound) ){
		if( optionList[i].GetOptionChar() == optionChar ){
			optionFound = true;
			if( optionList[i].GetOptionArgType() == optArgType::boolean ){
				if( optionList[i].SetOptionBooleanValue() == 1 ){
					optionAlreadySet =true;
				}
				if( verb > 1 )
					optionList[i].Dump();
			}
			else {
				optionIsBoolean = false;
			}
		}
		i++;
	}
	if ( optionAlreadySet){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::SetOptionValue: Option " << optionChar << " has been previously set." << std::endl;
		return 1;
	}
	if ( !optionFound ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::SetOptionValue: Option" << optionChar << " not found." << std::endl;
		return 1;
	}
	if ( !optionIsBoolean ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::SetOptionValue: Option " << optionChar << " requires an argument." << std::endl;
		return 1;
	}
	return 0;
}

int CLAcommandLine::SetOptionValue(char optionChar, char* value){
	uint8_t i = 0;
	bool optionFound = false;
	bool optionAlreadySet =false;
	bool optionInvalidArgument = false;
	bool optionIsBoolean = false;
	while( (i < optionList.size()) && (!optionFound) ){
		if( optionList[i].GetOptionChar() == optionChar ){
			optionFound = true;
			switch( optionList[i].GetOptionArgType() ){
			case optArgType::integer :
				try {
					int tmpint = std::stoi(value);
					if( optionList[i].SetOptionIntegerValue(tmpint) == 1 ){
						optionAlreadySet = true;
					}
					if( verb > 1 )
						optionList[i].Dump();
				}
				catch (const std::invalid_argument& ia){
					optionInvalidArgument = true;
					if( verb > 0 )
						std::cerr << "CLAcommandLine::SetOptionValue: Option " << optionChar << " invalid argument; " << ia.what() << '\n';
				}
				break;
			case optArgType::floating :
				try {
					float tmpfloat = std::stof(value);
					if( optionList[i].SetOptionFloatValue(tmpfloat) == 1 ){
						optionAlreadySet = true;
					}
					if( verb > 1 )
						optionList[i].Dump();
				}
				catch (const std::invalid_argument& ia){
					optionInvalidArgument = true;
					if( verb > 0 )
						std::cerr << "CLAcommandLine::SetOptionValue: Option " << optionChar << " invalid argument; " << ia.what() << '\n';
				}
				break;
			case optArgType::string :
				if( optionList[i].SetOptionStringValue(value) == 1 ){
					optionAlreadySet = true;
				}
				if( verb > 1 )
					optionList[i].Dump();
				break;
			case optArgType::boolean :
				optionIsBoolean = true;
			}
		}
		i++;
	}
	if ( optionAlreadySet){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::SetOptionValue: Option " << optionChar << " has been previously set." << std::endl;
		return 1;
	}
	if ( !optionFound ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::SetOptionValue: Option" << optionChar << " not found." << std::endl;
		return 1;
	}
	if ( optionIsBoolean ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::SetOptionValue: Option " << optionChar << " does not require an argument." << std::endl;
		return 1;
	}
	if (optionInvalidArgument ){
		return 1;
	}
	return 0;
}

int CLAcommandLine::SetOptionValue(std::string optionName){
	uint8_t i = 0;
	bool optionFound = false;
	bool optionAlreadySet =false;
	bool optionIsBoolean = true;
	while( (i < optionList.size()) && (!optionFound) ){
		if( optionName.compare( optionList[i].GetOptionName() ) == 0 ){
			optionFound = true;
			if( optionList[i].GetOptionArgType() == optArgType::boolean ){
				if( optionList[i].SetOptionBooleanValue() == 1 ){
					optionAlreadySet =true;
				}
				if( verb > 1 )
					optionList[i].Dump();
			}
			else {
				optionIsBoolean = false;
			}
		}
		i++;
	}
	if ( optionAlreadySet){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::SetOptionValue: Option " << optionName << " has been previously set." << std::endl;
		return 1;
	}
	if ( !optionFound ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::SetOptionValue: Option" << optionName << " not found." << std::endl;
		return 1;
	}
	if ( !optionIsBoolean ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::SetOptionValue: Option " << optionName << " requires an argument." << std::endl;
		return 1;
	}
	return 0;
}


int CLAcommandLine::SetOptionValue(std::string optionName, char* value){
	uint8_t i = 0;
	bool optionFound = false;
	bool optionAlreadySet =false;
	bool optionInvalidArgument = false;
	bool optionIsBoolean = false;
	while( (i < optionList.size()) && (!optionFound) ){
		if( optionName.compare( optionList[i].GetOptionName() ) == 0 ){
			optionFound = true;
			switch( optionList[i].GetOptionArgType() ){
			case optArgType::integer :
				try {
					int tmpint = std::stoi(value);
					if( optionList[i].SetOptionIntegerValue(tmpint) == 1 ){
						optionAlreadySet = true;
					}
					if( verb > 1 )
						optionList[i].Dump();
				}
				catch (const std::invalid_argument& ia){
					optionInvalidArgument = true;
					if( verb > 0 )
						std::cerr << "CLAcommandLine::SetOptionValue: Option " << optionName << " invalid argument; " << ia.what() << '\n';
				}
				break;
			case optArgType::floating :
				try {
					float tmpfloat = std::stof(value);
					if( optionList[i].SetOptionFloatValue(tmpfloat) == 1 ){
						optionAlreadySet = true;
					}
					if( verb > 1 )
						optionList[i].Dump();
				}
				catch (const std::invalid_argument& ia){
					optionInvalidArgument = true;
					if( verb > 0 )
						std::cerr << "CLAcommandLine::SetOptionValue: Option " << optionName << " invalid argument; " << ia.what() << '\n';
				}
				break;
			case optArgType::string :
				if( optionList[i].SetOptionStringValue(value) == 1 ){
					optionAlreadySet = true;
				}
				if( verb > 1 )
					optionList[i].Dump();
				break;
			case optArgType::boolean :
				optionIsBoolean = true;
			}
		}
		i++;
	}
	if ( optionAlreadySet){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::SetOptionValue: Option " << optionName << " has been previously set." << std::endl;
		return 1;
	}
	if ( !optionFound ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::SetOptionValue: Option" << optionName << " not found." << std::endl;
		return 1;
	}
	if ( optionIsBoolean ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::SetOptionValue: Option " << optionName << " does not require an argument." << std::endl;
		return 1;
	}
	if (optionInvalidArgument ){
		return 1;
	}
	return 0;
}

bool CLAcommandLine::GetOptionValue(std::string optionName){
	uint8_t i = 0;
	bool optionFound = false;
	bool optionAlreadySet = false;
	while( (i < optionList.size()) && (!optionFound) ){
		if( optionName.compare( optionList[i].GetOptionName() ) == 0 ){
			optionFound = true;
			if( optionList[i].IsSetValue() )
				optionAlreadySet = true;
		}
		i++;
	}
	if ( !optionAlreadySet ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::GetOptionValue: Option " << optionName << " is not present in command line arguments." << std::endl;
		return false;
	}
	if ( !optionFound ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::GetOptionValue: Option" << optionName << " not found." << std::endl;
		return false;
	}
	return true;
}

int CLAcommandLine::GetOptionValue(std::string optionName, std::string &value){
	uint8_t i = 0;
	bool optionFound = false;
	bool optionAlreadySet = false;
	bool optionIsString = true;
	while( (i < optionList.size()) && (!optionFound) ){
		if( optionName.compare( optionList[i].GetOptionName() ) == 0 ){
			optionFound = true;
			if( optionList[i].GetOptionArgType() == optArgType::string ){
				if( optionList[i].IsSetValue() ){
					optionAlreadySet = true;
					optionList[i].GetOptionValue(value);
				}
			}
			else {
				optionIsString = false;
			}
		}
		i++;
	}
	if ( !optionAlreadySet){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::GetOptionValue: Option " << optionName << " is not present in command line arguments." << std::endl;
		return 1;
	}
	if ( !optionFound ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::GetOptionValue: Option" << optionName << " not found." << std::endl;
		return 1;
	}
	if ( !optionIsString ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::GetOptionValue: Option" << optionName << " does not accept an string as argument." << std::endl;
		return 1;
	}
	return 0;
}

int CLAcommandLine::GetOptionValue(std::string optionName, int &value){
	uint8_t i = 0;
	bool optionFound = false;
	bool optionAlreadySet = false;
	bool optionIsInteger = true;
	while( (i < optionList.size()) && (!optionFound) ){
		if( optionName.compare( optionList[i].GetOptionName() ) == 0 ){
			optionFound = true;
			if( optionList[i].GetOptionArgType() == optArgType::integer ){
				if( optionList[i].IsSetValue() ){
					optionAlreadySet = true;
					optionList[i].GetOptionValue(value);
				}
			}
			else {
				optionIsInteger = false;
			}
		}
		i++;
	}
	if ( !optionAlreadySet){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::GetOptionValue: Option " << optionName << " is not present in command line arguments." << std::endl;
		return 1;
	}
	if ( !optionFound ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::GetOptionValue: Option" << optionName << " not found." << std::endl;
		return 1;
	}
	if ( !optionIsInteger ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::GetOptionValue: Option" << optionName << " argument is not integer type." << std::endl;
		return 1;
	}
	return 0;
}

int CLAcommandLine::GetOptionValue(std::string optionName, float &value){
	uint8_t i = 0;
	bool optionFound = false;
	bool optionAlreadySet = false;
	bool optionIsFloat = true;
	while( (i < optionList.size()) && (!optionFound) ){
		if( optionName.compare( optionList[i].GetOptionName() ) == 0 ){
			optionFound = true;
			if( optionList[i].GetOptionArgType() == optArgType::floating ){
				if( optionList[i].IsSetValue() ){
					optionAlreadySet = true;
					optionList[i].GetOptionValue(value);
				}
			}
			else {
				optionIsFloat = false;
			}
		}
		i++;
	}
	if ( !optionAlreadySet){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::GetOptionValue: Option " << optionName << " is not present in command line arguments." << std::endl;
		return 1;
	}
	if ( !optionFound ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::GetOptionValue: Option" << optionName << " not found." << std::endl;
		return 1;
	}
	if ( !optionIsFloat ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::GetOptionValue: Option" << optionName << " argument is not float type." << std::endl;
		return 1;
	}
	return 0;
}

bool CLAcommandLine::OptionExpectsArgument(char optionChar){
	uint8_t i = 0;
	bool optionFound = false;
	bool argumentExpected = false;
	while( (i < optionList.size()) && (!optionFound) ){
		if( optionList[i].GetOptionChar() == optionChar ){
			optionFound = true;
			if( optionList[i].GetOptionArgType() != optArgType::boolean )
				argumentExpected = true;
		}
		i++;
	}
	return argumentExpected;
}

bool CLAcommandLine::OptionExpectsArgument(std::string optionName){
	uint8_t i = 0;
	bool optionFound = false;
	bool argumentExpected = false;
	while( (i < optionList.size()) && (!optionFound) ){
		if( optionName.compare( optionList[i].GetOptionName() ) == 0 ){
			optionFound = true;
			if( optionList[i].GetOptionArgType() != optArgType::boolean )
				argumentExpected = true;
		}
		i++;
	}
	return argumentExpected;
}


int CLAcommandLine::AddGlobalArgument(std::string globalArgumentName, std::string globalArgumentDescription){
	CLAdglobalArgument newGlobalArgument( globalArgumentName, globalArgumentDescription, gargCount++);
	gargsList.push_back(newGlobalArgument);
	return 0;
}

bool CLAcommandLine::FindGlobalArgument(uint8_t globalArgumentPosition){
	uint8_t i = 0;
	bool isPresent = false;
	while( (i < gargsList.size()) && (!isPresent) ){
		if( gargsList[i].GetArgumentPosition() == globalArgumentPosition )
			isPresent = true;
		i++;
	}
	return isPresent;
}

int CLAcommandLine::SetGlobalArgumentValue(uint8_t globalArgumentPosition, char* value){
	uint8_t i = 0;
	bool gargFound = false;
	bool gargAlreadySet =false;
	int foundArgPos;
	while( (i < gargsList.size()) && (!gargFound) ){
		if( gargsList[i].GetArgumentPosition() == globalArgumentPosition ){
			gargFound = true;
			if( gargsList[i].SetArgumentValue(value) == 1 ){
				gargAlreadySet = true;
				foundArgPos = i;
			}
			if( verb > 1 )
				gargsList[i].Dump();
		}
		i++;
	}
	if ( gargAlreadySet){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::SetGlobalArgumentValue: " << gargsList[ foundArgPos ].GetArgumentName( ) << " argument has been previously set." << std::endl;
		return 1;
	}
	if ( !gargFound ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::SetGlobalArgumentValue: "<< globalArgumentPosition << " No argument at this position." << std::endl;
		return 1;
	}

	return 0;
}

int CLAcommandLine::GetGlobalArgumentValue(std::string globalArgumentName, std::string &value){
	uint8_t i = 0;
	bool argFound = false;
	bool argAlreadySet = false;
	while( (i < gargsList.size()) && (!argFound) ){
		if( globalArgumentName.compare( gargsList[i].GetArgumentName() ) == 0 ){
			argFound = true;
			if( gargsList[i].IsSetValue() ){
				argAlreadySet = true;
				value = gargsList[i].GetArgumentValue();
			}
		}
		i++;
	}
	if ( !argAlreadySet){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::SetGlobalArgumentValue: "<< globalArgumentName << " This argument is not present in command line." << std::endl;
		return 1;
	}
	if ( !argFound ){
		if( verb > 0 )
			std::cerr << "CLAcommandLine::SetGlobalArgumentValue: "<< globalArgumentName << " No argument at this position." << std::endl;
		return 1;
	}
	return 0;
}

bool CLAcommandLine::AllGlobalArgumentsFound(){
	bool allArgsSet = true;
	for(uint8_t i = 0 ; i < gargsList.size() ; i++ )
		if( !gargsList[i].IsSetValue() )
			allArgsSet = false;
	return allArgsSet;

}


void CLAcommandLine::PrintUsageMessage(std::string commandName){
	if( !programDescription.empty() )
		std::cout << "\n" << programDescription << std::endl;
	std::cout << "\nUSAGE:\n";
	std::cout << "\t" << commandName << " ";
	if( optionList.size() > 0 )
		std::cout << " <options> ";
	if( gargsList.size() > 0 ){
		for( uint8_t i = 0 ; i < gargsList.size() ; i++ )
			std::cout << gargsList[i].GetArgumentName() << " ";
	}
	std::cout << "\n";

	if( optionList.size() > 0 ){
		std::cout << "\nOptions:\n";
		for(uint8_t i = 0 ; i < optionList.size() ; i++ ){
			std::cout << "\t--" << optionList[i].GetOptionName();
			if( optionList[i].GetOptionChar() != 0 )
				std::cout << ",\t-" << optionList[i].GetOptionChar();
			else
				std::cout << "\t";
			std::cout << "\t" << optionList[i].GetOptionDescription() << std::endl;
		}
	}
	std::cout << "\n";

	if( gargsList.size() > 0 ){
		std::cout << "\nObligatory arguments:\n";
		for( uint8_t i = 0 ; i < gargsList.size() ; i++ )
			std::cout << "\t" << gargsList[i].GetArgumentName() << "\t\t" << gargsList[i].GetArgumentDescription() << std::endl;
	}
	std::cout << "\n";
}


void CLAcommandLine::AddProgramDescription(std::string description){
	programDescription = description;
}


bool CLAcommandLine::Parse(int argCount, char** argVector){
	int argCounter = 0;

	bool optionParseError = false;

	for(int i= 1 ; i < argCount ; i++){
		if( (argVector[i])[0] == '-'){
			if( (argVector[i])[1] != '-'){
				if( FindOption( (argVector[i])[1]) ){
					if( verb > 1 )
						std::cout << "CLAcommandLine::Parse: Valid option found "<< (argVector[i])[1] << std::endl;
					if( OptionExpectsArgument( (argVector[i])[1] ) ) {
						if(  (i+1) < argCount ){
							if( (argVector[i+1])[0] != '-'){
								if( ( SetOptionValue( (argVector[i])[1] , argVector[i+1] ) ) == 1 ){
									if( verb > 0 )
										std::cerr << "CLAcommandLine::Parse: Invalid option "<< argVector[i] << " argument: " <<  argVector[i+1] << std::endl;
									optionParseError = true;
									break;
								}
								i++;
							}
							else {
								if( verb > 0 )
									std::cerr << "CLAcommandLine::Parse: Option " <<  argVector[i] << ": argument expected" << std::endl;
								optionParseError = true;
								break;

							}
						}
						else {
							if( verb > 0 )
								std::cerr << "CLAcommandLine::Parse: Option " <<  argVector[i] << ": argument expected" << std::endl;
							optionParseError = true;
							break;
						}
					}
					else {
						if( ( SetOptionValue( (argVector[i])[1] ) ) == 1 ){
							if( verb > 0 )
								std::cerr << "CLAcommandLine::Parse: Invalid option "<< argVector[i] << " argument: " <<  argVector[i+1] << std::endl;
							optionParseError = true;
							break;
						}
					}
				}
				else {
					if( verb > 0 )
						std::cerr << "CLAcommandLine::Parse: Invalid option: " << argVector[i] << std::endl;
					optionParseError = true;
					break;
				}
			}
			else {
				std::string tmp = argVector[i];
				std::string lopt = tmp.substr( 2, tmp.size()-2 );
				if( FindOption( lopt ) ){
					if( verb > 1 )
						std::cout << "CLAcommandLine::Parse: Valid option found "<< lopt << std::endl;
					if( OptionExpectsArgument( lopt ) ) {
						if(  (i+1) < argCount ){
							if( (argVector[i+1])[0] != '-'){
								if( ( SetOptionValue( lopt , argVector[i+1] ) ) == 1 ){
									if( verb > 0 )
										std::cerr << "CLAcommandLine::Parse: Invalid option "<< argVector[i] << " argument: " <<  argVector[i+1] << std::endl;
									optionParseError = true;
									break;
								}
								i++;
							}
							else {
								if( verb > 0 )
									std::cerr << "CLAcommandLine::Parse: Option " <<  argVector[i] << ": argument expected" << std::endl;
								optionParseError = true;
								break;

							}
						}
						else {
							if( verb > 0 )
								std::cerr << "CLAcommandLine::Parse: Option " <<  argVector[i] << ": argument expected" << std::endl;
							optionParseError = true;
							break;

						}
					}
					else {
						if( ( SetOptionValue( lopt ) ) == 1 ){
							if( verb > 0 )
								std::cerr << "CLAcommandLine::Parse: Invalid option "<< argVector[i] << " argument: " <<  argVector[i+1] << std::endl;
							optionParseError = true;
							break;
						}
					}
				}
				else {
					if( verb > 0 )
						std::cerr << "CLAcommandLine::Parse: Invalid option " << argVector[i]  << std::endl;
					optionParseError = true;
					break;
				}
			}
		}
		else {
			if( SetGlobalArgumentValue( argCounter++, argVector[i]) == 1 ){
				if( verb > 0 )
					std::cerr << "CLAcommandLine::Parse: Invalid argument "<< argVector[i] << std::endl;
				optionParseError = true;
				break;
			}
		}
	}

	if( !optionParseError && AllGlobalArgumentsFound() )
		return true;
	else
		return false;
}
