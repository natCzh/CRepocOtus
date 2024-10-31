#ifndef _COMMAND_INTERPRET_COMMAND_H_
#define _COMMAND_INTERPRET_COMMAND_H_

#include "IoC/IoCGlobal.h"
#include "Command/ICommand.h"

class CommandInterpretCommand_StartMove: public ICommand
{
public:

	CommandInterpretCommand_StartMove()
	{}

	void Execute() override
	{
		ioc.Resolve<std::shared_ptr<UObject> >("" )






		std::cout << "Error in dictionary" << std::endl;
	}

	std::string GetType() override
	{
		return "CommandInterpretCommand_StartMove";
	}
};

#endif /* _COMMAND_INTERPRET_COMMAND_H_ */
