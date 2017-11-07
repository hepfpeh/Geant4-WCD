/*
 * CLAoption.hh
 *
 *  Created on: 21/11/2016
 *      Author: hepf
 */

#ifndef INCLUDE_CLAOPTION_HH_
#define INCLUDE_CLAOPTION_HH_

#include <string>

/**
 * CLAoption class.
 * This is a basic class for handling options.
 *
 * This class implements:
 * - option name or long name
 * - option char
 * - option value as string
 *
 * and the respective set and get methods.
 */
class CLAoption{

public:
	CLAoption();
	virtual ~CLAoption();

	int SetOptionName(std::string optionName);
	int SetOptionChar(char optionChar);
	int SetOptionValue(char *optionValue);

	virtual std::string	GetOptionName();
	virtual char		GetOptionChar();
	virtual std::string	GetOptionValue();

	/**
	 * This method returns true if the option value has been set.
	 */
	virtual bool IsSetValue();

	/**
	 * Dumps all data members values.
	 */
	virtual void Dump();

protected:
	std::string optName;
	char optChar;
	std::string optValue;

};


#endif /* INCLUDE_CLAOPTION_HH_ */
