/*
 * gargument.cc
 *
 *  Created on: 22/11/2016
 *      Author: hepf
 */

#include "CLAglbarg.hh"
#include <cstdint>
#include <string>
#include <iostream>

CLAglobalArgument::CLAglobalArgument(){
	argPosition = 0;
}

CLAglobalArgument::~CLAglobalArgument(){}

int CLAglobalArgument::SetArgumentValue(std::string value){
	if( argValue.empty() ){
		argValue = value;
		return 0;
	}
	else {
		std::cerr << "Argument value has been already set!";
		return 1;
	}
}

int CLAglobalArgument::GetArgumentPosition(){
	return argPosition;
}

std::string CLAglobalArgument::GetArgumentValue(){
	return argValue;
}

bool CLAglobalArgument::IsSetValue(){
	return !( argValue.empty() );
}

void CLAglobalArgument::Dump(){
	std::cout <<"\t<" << (int)argPosition << ">\t<" << argValue << ">" << std::endl;
}
