#ifndef _COMMAND_INTERPRET_COMMAND_PREPARE_FOR_MOVE_H_
#define _COMMAND_INTERPRET_COMMAND_PREPARE_FOR_MOVE_H_

#include <memory>

#include "Command/ICommand.h"
#include "Exception/InterpretCommandException.h"
#include "CommonLib/IMessagable.h"
#include "CommonLib/UObject.h"

class CommandInterpretCommand_PrepareForMove : public ICommand
{
public:

    CommandInterpretCommand_PrepareForMove(UObject_Ptr obj_, IMessagable_Ptr messagable_)
		: obj(obj_)
		, messagable(messagable_)
	{}

	void Execute() override
	{
        std::map<std::string, boost::any> mapPropCur = messagable->getProperties();

        auto valVel = std::find(mapPropCur.begin(), mapPropCur.end(), "velocity");
        if (valVel == mapPropCur.end())
            InterpretCommandException("UObject messagable - velocity isn't exist");

        obj->setProperty("velocity", valVel);
	}

	std::string GetType() override
	{
		return "CommandInterpret.PrepareForMove";
	}

protected:
    UObject_Ptr             									obj;
    IMessagable_Ptr                                 			messagable;
};

#endif /* _COMMAND_INTERPRET_COMMAND_PREPARE_FOR_MOVE_H_ */
