/*
 * gargument.cc
 *
 *  Created on: 22/11/2016
 *      Author: hepf
 */

#include "CLAdglbarg.hh"
#include <cstdint>
#include <string>
#include <iostream>

CLAdglobalArgument::CLAdglobalArgument(std::string name, std::string description, uint8_t position){
	argName = name;
	argDescription = description;
	argPosition = position;
}

std::string CLAdglobalArgument::GetArgumentName(){
	return argName;
}

std::string CLAdglobalArgument::GetArgumentDescription(){
	return argDescription;
}

void CLAdglobalArgument::Dump(){
	std::cout << argName << "\t<" << (int)argPosition << ">\t<" << argValue << ">" << std::endl;
}
