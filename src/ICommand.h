#ifndef _I_COMMAND_H_
#define _I_COMMAND_H_

#include <string>
#include <iostream>


class ICommand
{
public:
	virtual int Execute() = 0;

	virtual std::string GetType() = 0;
};

using ICommand_Ptr = std::shared_ptr<ICommand>;

class CommandErrorDefault: public ICommand
{
public:
	int Execute() override
	{
		std::cout << "Error in dictionary" << std::endl;

		return 0;
	}

	std::string GetType() override
	{
		return "CommandErrorDefault";
	}
};

#endif _I_COMMAND_H_