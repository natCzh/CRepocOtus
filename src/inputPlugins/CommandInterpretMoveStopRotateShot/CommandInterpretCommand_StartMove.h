#ifndef _COMMAND_INTERPRET_COMMAND_START_MOVE_H_
#define _COMMAND_INTERPRET_COMMAND_START_MOVE_H_

#include <memory>

#include "IoC/IoC.h"
#include "Common/QueueCommand.h"
#include "CommonLib/IMessagable.h"
#include "CommonLib/UObject.h"
#include "Command/IBridgeCommand.h"

extern IoC* ioc;
class CommandInterpretCommand_StartMove: public ICommand
{
public:

    CommandInterpretCommand_StartMove(IMessagable_Ptr messagable_, std::shared_ptr<QueueCommand> queue_)
		: messagable(messagable_)
		, queue(queue_)
	{}

	void Execute() override
	{
        // так как в Interpret уже выставлен scope для нужной игры, мы просто получаем нужный объект
        std::shared_ptr<UObject> curObject = ioc->Resolve<std::shared_ptr<UObject> >(
            "GameItems", messagable->getIdObject());
        ioc->Resolve<ICommand_Ptr>(
			"CommandInterpret.PrepareForMove",
			curObject,
			messagable);

        ICommand_Ptr cmd = ioc->Resolve<ICommand_Ptr>("Command.MoveLongOperation", messagable->getIdObject(), queue);
		queue->Push(cmd);

        auto cmdBridg = std::dynamic_pointer_cast<IBridgeCommand_Ptr>(cmd);
        curObject->setProperty("Move", cmdBridg);
	}

	std::string GetType() override
	{
        return "CommandInterpret.StartMove";
	}

protected:
    IMessagable_Ptr             						messagable;
	std::shared_ptr<QueueCommand>						queue;
};

#endif /* _COMMAND_INTERPRET_COMMAND_START_MOVE_H_ */
