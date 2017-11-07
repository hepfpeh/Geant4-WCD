/*
* clap.hh
*/

#ifndef INCLUDE_CLACMDLN_HH_
#define INCLUDE_CLACMDLN_HH_

#include <string>
#include <vector>
#include <cstdint>

#include "CLAtdopt.hh"
#include "CLAdglbarg.hh"

class CLAtdoption;
class CLAglobalArgument;

class CLAcommandLine {
public:

	CLAcommandLine( uint8_t verbousity = 0 );

	/*
	 *  Options methods
	 */

	int AddOption(std::string optionName, char optionChar, std::string optionDescription, optArgType optionArgumentType);

	bool FindOption(char optionChar);
	bool FindOption(std::string optionName);

	int SetOptionValue(char optionChar);
	int SetOptionValue(char optionChar, char* value);
	int SetOptionValue(std::string optionName);
	int SetOptionValue(std::string optionName, char* value);

	bool GetOptionValue(std::string optionName);
	int GetOptionValue(std::string optionName, std::string &value);
	int GetOptionValue(std::string optionName, int &value);
	int GetOptionValue(std::string optionName, float &value);

	bool OptionExpectsArgument(char optionChar);
	bool OptionExpectsArgument(std::string optionName);

	/*
	 * Global arguments methods
	 */


	int AddGlobalArgument(std::string globalArgumentName, std::string globalArgumentDescription);

	bool FindGlobalArgument(uint8_t globalArgumentPosition);

	int SetGlobalArgumentValue(uint8_t globalArgumentPosition, char* value);

	int GetGlobalArgumentValue(std::string globalArgumentName, std::string &value);

	bool AllGlobalArgumentsFound();

	/*
	 * General methods
	 */

	void PrintUsageMessage(std::string commandName);
	void AddProgramDescription(std::string description);
	bool Parse(int argCount, char** argVector);

private:
	std::vector<CLAtdoption> optionList;
	std::vector<CLAdglobalArgument> gargsList;
	std::string programDescription;
	uint8_t gargCount;

	uint8_t verb;

};




#endif /* INCLUDE_CLACMDLN_HH_ */
