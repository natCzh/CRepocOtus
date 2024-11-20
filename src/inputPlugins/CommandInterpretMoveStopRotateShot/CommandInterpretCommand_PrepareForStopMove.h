#ifndef _COMMAND_INTERPRET_COMMAND_PREPARE_FOR_STOP_MOVE_H_
#define _COMMAND_INTERPRET_COMMAND_PREPARE_FOR_STOP_MOVE_H_

#include <memory>

#include "Command/ICommand.h"
#include "CommonLib/UObject.h"

class CommandInterpretCommand_PrepareForStopMove : public ICommand
{
public:

    CommandInterpretCommand_PrepareForStopMove(UObject_Ptr obj_)
		: obj(obj_)
	{}

	void Execute() override
	{
        obj->setProperty("velocity", 0);
	}

	std::string GetType() override
	{
        return "CommandInterpret.PrepareForStopMove";
	}

protected:
    UObject_Ptr             									obj;
};

#endif /* _COMMAND_INTERPRET_COMMAND_PREPARE_FOR_STOP_MOVE_H_ */
