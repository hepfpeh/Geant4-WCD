/*
 * gargument.hh
 *
 *  Created on: 22/11/2016
 *      Author: hepf
 */

#ifndef INCLUDE_GARGUMENT_HH_
#define INCLUDE_GARGUMENT_HH_

#include <string>
#include <cstdint>

class CLAglobalArgument {
public:
	CLAglobalArgument();
	virtual ~CLAglobalArgument();

	int SetArgumentPosition(uint8_t position);
	int SetArgumentValue(std::string value);

	int GetArgumentPosition();
	std::string GetArgumentValue();

	virtual bool IsSetValue();

	virtual void Dump();

protected:
	uint8_t argPosition;
	std::string argValue;
};


#endif /* INCLUDE_GARGUMENT_HH_ */
