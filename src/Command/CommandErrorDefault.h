#ifndef _COMMAND_ERROR_DEFAULT_H_
#define _COMMAND_ERROR_DEFAULT_H_

#include "Command/ICommand.h"

class CommandErrorDefault: public ICommand
{
public:
	void Execute() override
	{
		std::cout << "Error in dictionary" << std::endl;
	}

	std::string GetType() override
	{
		return "CommandErrorDefault";
	}
};

#endif /* _COMMAND_ERROR_DEFAULT_H_ */
