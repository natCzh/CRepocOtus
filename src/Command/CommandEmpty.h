#ifndef _COMMAND_EMPTY_H_
#define _COMMAND_EMPTY_H_

#include "Command/ICommand.h"

class CommandEmpty: public ICommand
{
public:

	virtual ~CommandEmpty() {}

	void Execute() {}

	std::string GetType() { return "CommandEmpty"; }
};

#endif /* _COMMAND_EMPTY_H_ */