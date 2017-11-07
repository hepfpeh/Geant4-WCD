/*
 * CLAtdoption.cc
 *
 *  Created on: 21/11/2016
 *      Author: hepf
 */

#include "CLAtdopt.hh"
#include <string>
#include <iostream>

CLAtdoption::CLAtdoption(std::string name){
	optName = name;
	optChar = 0;
	optDescription = "Please add a description";
	optArgumentType = optArgType::boolean;
	optBooleanValue = false;
	optIntegerValue = -1;
	optFloatValue = -1.0;
}

CLAtdoption::CLAtdoption(std::string name, char ochar, std::string description, optArgType type){
	optName = name;
	optChar = ochar;
	optDescription = description;
	optArgumentType = type;
	optBooleanValue = false;
	optIntegerValue = -1;
	optFloatValue = -1.0;

}

int CLAtdoption::SetOptionDescription(std::string description){
	optDescription = description;
	return 0;
}

int CLAtdoption::SetOptionArgType(optArgType type){
	optArgumentType = type;
	return 0;
}


int CLAtdoption::SetOptionBooleanValue(){
	if( !optBooleanValue){
		optBooleanValue = true;
		return 0;
	}
	else {
		std::cerr << "option value has been already set!" << std::endl;
		return 1;
	}
}

int CLAtdoption::SetOptionIntegerValue(int value){
	if( !optBooleanValue){
		optBooleanValue = true;
		optIntegerValue = value;
		return 0;
	}
	else {
		std::cerr << "option value has been already set!" << std::endl;
		return 1;
	}

}

int CLAtdoption::SetOptionFloatValue(float value){
	if( !optBooleanValue){
		optBooleanValue = true;
		optFloatValue = value;
		return 0;
	}
	else {
		std::cerr << "option value has been already set!" << std::endl;
		return 1;
	}

}

int CLAtdoption::SetOptionStringValue(char *value){
	if( !optBooleanValue){
		optBooleanValue = true;
		optValue = value;
		return 0;
	}
	else {
		std::cerr << "option value has been already set!" << std::endl;
		return 1;
	}
}

std::string CLAtdoption::GetOptionDescription(){
	return optDescription;
}

optArgType CLAtdoption::GetOptionArgType(){
	return optArgumentType;
}

int CLAtdoption::GetOptionValue(int &value){
	if( optBooleanValue ){
		value = optIntegerValue;
		return 0;
	}
	else {
		std::cerr << "Option argument has not been set!" << std::endl;
		return 1;
	}
}

int CLAtdoption::GetOptionValue(float &value){
	if( optBooleanValue ){
		value = optFloatValue;
		return 0;
	}
	else {
		std::cerr << "Option argument has not been set!" << std::endl;
		return 1;
	}
}

int CLAtdoption::GetOptionValue(std::string &value){
	if( optBooleanValue ){
		value = optValue;
		return 0;
	}
	else {
		std::cerr << "Option argument has not been set!" << std::endl;
		return 1;
	}
}

bool CLAtdoption::IsSetValue(){
	return optBooleanValue;
}


void CLAtdoption::Dump(){
	std::cout << optName << "\t<" << optBooleanValue << ">\t<" << optIntegerValue << ">\t<" << optValue << ">" << std::endl;
}
