#ifndef _COMMAND_INTERPRET_COMMAND_PREPARE_FOR_SHOT_H_
#define _COMMAND_INTERPRET_COMMAND_PREPARE_FOR_SHOT_H_

#include <boost/any.hpp>

#include "Command/ICommand.h"
#include "Exception/InterpretCommandException.h"
#include "CommonLib/UObject.h"

class CommandInterpretCommand_PrepareForShot : public ICommand
{
public:

    CommandInterpretCommand_PrepareForShot(UObject_Ptr obj_)
        : obj(obj_)
	{}

	void Execute() override
	{
        auto numberShotValueAny = obj->getProperty("numberShot");
        size_t numberShotValue = boost::any_cast<size_t>(numberShotValueAny);
        if(numberShotValue < 0)
            throw InterpretCommandException("UObject - command shot isn't possible");
	}

	std::string GetType() override
	{
        return "CommandInterpret.PrepareForShot";
	}

protected:
    UObject_Ptr             									obj;
};

#endif /* _COMMAND_INTERPRET_COMMAND_PREPARE_FOR_SHOT_H_ */
