#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <iostream>

#include "ICommand.h"

///////////////////////////////////////////////////////////////
///////////////// Команды
class HardStop: public ICommand
{
public:
	void Execute()
	{
		std::cout << "execute HardStop" << std::endl;
	}

	std::string GetType()
	{
		return "HardStop";
	}
};

class MoveToCommand: public ICommand
{
public:
	void Execute()
	{
		std::cout << "execute MoveToCommand" << std::endl;
	}

	std::string GetType()
	{
		return "MoveToCommand";
	}
};

class RunCommand: public ICommand
{
public:
	void Execute()
	{
		std::cout << "execute RunCommand" << std::endl;
	}

	std::string GetType()
	{
		return "RunCommand";
	}
};

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

#endif /* _COMMAND_H_*/