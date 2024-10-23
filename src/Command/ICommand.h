#ifndef _I_COMMAND_H_
#define _I_COMMAND_H_

#include <string>
#include <iostream>

class ICommand
{
public:
	virtual ~ICommand() {}

	virtual void Execute() = 0;

	virtual std::string GetType() = 0;
};

using ICommand_Ptr = std::shared_ptr<ICommand>;

class CommandEmpty: public ICommand
{
public:
	void Execute()
	{
		std::cout << "execute CommandEmpty" << std::endl;
	}

	std::string GetType()
	{
		return "CommandEmpty";
	}
};

#endif /* _I_COMMAND_H_ */