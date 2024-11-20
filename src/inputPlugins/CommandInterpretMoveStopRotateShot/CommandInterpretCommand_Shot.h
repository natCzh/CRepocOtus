#ifndef _COMMAND_INTERPRET_COMMAND_SHOT_H_
#define _COMMAND_INTERPRET_COMMAND_SHOT_H_

#include "boost/any.hpp"

#include "IoC/IoC.h"
#include "CommonLib/IMessagable.h"
#include "Common/QueueCommand.h"
#include "CommonLib/UObject.h"
// #include "Exception/InterpretCommandException.h"

extern IoC* ioc;
class CommandInterpretCommand_Shot: public ICommand
{
public:


    /// @param[in] directionRotate - направление поворота 1 - по часовой, -1 - против часовой
    CommandInterpretCommand_Shot(IMessagable_Ptr messagable_, std::shared_ptr<QueueCommand> queue_)
		: messagable(messagable_)
        , queue(queue_)
	{}

	void Execute() override
	{
        // так как в Interpret уже выставлен scope для нужной игры, мы просто получаем нужный объект
        UObject_Ptr curObject = ioc->Resolve<UObject_Ptr>(
            "GameItems", messagable->getIdObject());

        ioc->Resolve<ICommand_Ptr>(
            "CommandInterpret.PrepareForShot",
            curObject)->Execute();

        ICommand_Ptr cmd = ioc->Resolve<ICommand_Ptr>("Command.Shot", curObject);
        queue->Push(cmd);
	}

	std::string GetType() override
	{
        return "CommandInterpret.Shot";
	}

protected:
    IMessagable_Ptr             						messagable;
    std::shared_ptr<QueueCommand>                       queue;
};

#endif /* _COMMAND_INTERPRET_COMMAND_SHOT_H_ */
