#ifndef _MOVE_COMMAND_H_
#define _MOVE_COMMAND_H_

#include "src/Command/ICommand.h"

class MoveCommand: public ICommand
{
public:
	void Execute()
	{

	}

	std::string GetType()
	{
		return "MoveCommand";
	}
};

#endif /* #define _MOVE_COMMAND_H_
 */