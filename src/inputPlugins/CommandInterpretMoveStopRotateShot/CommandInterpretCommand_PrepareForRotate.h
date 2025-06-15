#ifndef _COMMAND_INTERPRET_COMMAND_PREPARE_FOR_ROTATE_H_
#define _COMMAND_INTERPRET_COMMAND_PREPARE_FOR_ROTATE_H_

#include <memory>

#include "Command/ICommand.h"
#include "Exception/InterpretCommandException.h"
#include "CommonLib/IMessagable.h"
#include "CommonLib/UObject.h"

class CommandInterpretCommand_PrepareForRotate : public ICommand
{
public:

    CommandInterpretCommand_PrepareForRotate(UObject_Ptr obj_, int directionRotate_)
		: obj(obj_)
        , directionRotate(directionRotate_)
	{}

	void Execute() override
	{
        if (directionRotate != 1 && directionRotate != -1)
            throw InterpretCommandException("UObject set - directionRotate isn't correct");
        boost::any anyDirectionRotate = directionRotate;
        obj->setProperty("directionAngular", anyDirectionRotate);
	}

	std::string GetType() override
	{
        return "CommandInterpret.PrepareForRotate";
	}

protected:
    UObject_Ptr             									obj;
    int                                              			directionRotate;
};

#endif /* _COMMAND_INTERPRET_COMMAND_PREPARE_FOR_ROTATE_H_ */
