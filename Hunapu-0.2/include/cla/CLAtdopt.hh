/*
 * CLAtdoption.hh
 *
 *  Created on: 21/11/2016
 *      Author: hepf
 */

#ifndef INCLUDE_TDOPTION_HH_
#define INCLUDE_TDOPTION_HH_

#include "CLAopt.hh"
#include <string>

/**
 * optArgType enum.
 * This enum specifies the type of argument an option will accept.
 * The boolean type is for options that only matter if they are present
 * or not. Does not accept any value.
 */
enum class optArgType { boolean, integer, floating, string };

/**
 * CLAtdoption class.
 *
 * This class extends CLAoption to include:
 * - option descriptions.
 * - option value types (integer & float).
 * - boolean options that does not accept any value.
 */
class CLAtdoption: public CLAoption {

public:
	CLAtdoption(std::string name);
	CLAtdoption(std::string name, char ochar, std::string desc, optArgType type);

	int SetOptionDescription(std::string desc);
	int SetOptionArgType(optArgType type);
	int SetOptionBooleanValue();
	int SetOptionIntegerValue(int value);
	int SetOptionFloatValue(float value);
	int SetOptionStringValue(char *value);

	std::string	GetOptionDescription();
	optArgType	GetOptionArgType();
	using 		CLAoption::GetOptionValue;
	int			GetOptionValue(int &value);
	int			GetOptionValue(float &value);
	int			GetOptionValue(std::string &value);

	bool IsSetValue();

	void Dump();

private:
	std::string optDescription;
	optArgType optArgumentType;

	bool optBooleanValue;
	int optIntegerValue;
	float optFloatValue;
};


#endif /* INCLUDE_TDOPTION_HH_ */
