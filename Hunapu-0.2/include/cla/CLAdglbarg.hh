/*
 * gargument.hh
 *
 *  Created on: 22/11/2016
 *      Author: hepf
 */

#ifndef INCLUDE_DGARGUMENT_HH_
#define INCLUDE_DGARGUMENT_HH_

#include "CLAglbarg.hh"
#include <string>
#include <cstdint>

class CLAdglobalArgument: public CLAglobalArgument {
public:
	CLAdglobalArgument(std::string name, std::string description, uint8_t position);

	std::string GetArgumentName();
	std::string GetArgumentDescription();

	void Dump();

private:
	std::string argName;
	std::string argDescription;
};


#endif /* INCLUDE_DGARGUMENT_HH_ */
