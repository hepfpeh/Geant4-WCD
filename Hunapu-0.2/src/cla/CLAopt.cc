/*
 * CLAoption.cc
 *
 *  Created on: 21/11/2016
 *      Author: hepf
 */

#include "CLAopt.hh"
#include <string>
#include <iostream>

CLAoption::CLAoption(){
	optChar = 0;
}

CLAoption::~CLAoption(){}

int CLAoption::SetOptionName(std::string optionName){
	if ( optName.empty() ) {
		optName = optionName;
		return 0;
	}
	else {
		std::cerr << "Option Name already set!" << std::endl;
		return 1;
	}
}

int CLAoption::SetOptionChar(char optionChar){
	if ( optChar == 0 ) {
		optChar = optionChar;
		return 0;
	}
	else {
		std::cerr << "Option letter already set!" << std::endl;
		return 1;
	}
}

int CLAoption::SetOptionValue(char *value){
	if( optValue.empty() ){
		optValue = value;
		return 0;
	}
	else {
		std::cerr << "Option value has been already set!" << std::endl;
		return 1;
	}
}

std::string CLAoption::GetOptionName(){
	if ( optName.empty() ) {
		std::cerr << "Option Name has not been set!" << std::endl;
		return optName;
	}
	else {
		return optName;
	}

}

char CLAoption::GetOptionChar(){
	if ( optChar == 0 ) {
		std::cerr << "Option char has not been set!" << std::endl;
		return 1;
	}
	else {
		return optChar;
	}

}

std::string CLAoption::GetOptionValue(){
	return optValue;
}

bool CLAoption::IsSetValue(){
	return !optValue.empty();
}


void CLAoption::Dump(){
	std::cout << "\t<" << optName << ">\t<" << optChar << ">\t<" << optValue << ">" << std::endl;
}
