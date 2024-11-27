#ifndef _COMMAND_INTERPRET_COMMAND_STOP_MOVE_H_
#define _COMMAND_INTERPRET_COMMAND_STOP_MOVE_H_

#include <memory>
#include "boost/any.hpp"

#include "IoC/IoC.h"
#include "CommonLib/IMessagable.h"
#include "Common/QueueCommand.h"
#include "CommonLib/UObject.h"
#include "Command/IBridgeCommand.h"
#include "Command/CommandEmpty.h"

extern IoC* ioc;
class CommandInterpretCommand_StopMove: public ICommand
{
public:

    CommandInterpretCommand_StopMove(IMessagable_Ptr messagable_, std::shared_ptr<QueueCommand> queue_)
		: messagable(messagable_)
	{}

	void Execute() override
	{
        // так как в Interpret уже выставлен scope для нужной игры, мы просто получаем нужный объект
        std::unordered_map<unsigned long long, UObject_Ptr> curVectObject = ioc->Resolve<std::unordered_map<unsigned long long, UObject_Ptr> >(
            "GameItems");
        UObject_Ptr curObject = curVectObject.find(messagable->getIdObject())->second;

        ioc->Resolve<ICommand_Ptr>(
            "CommandInterpret.PrepareForStopMove",
            curObject)->Execute();

        boost::any property = curObject->getProperty("Move");
        IBridgeCommand_Ptr cmd = boost::any_cast<IBridgeCommand_Ptr>(property);
        ICommand_Ptr cmdEmpty = std::make_shared<CommandEmpty>();
        cmd->Inject(cmdEmpty);
	}

	std::string GetType() override
	{
        return "CommandInterpret.StopMove";
	}

protected:
    IMessagable_Ptr             						messagable;
};

#endif /* _COMMAND_INTERPRET_COMMAND_STOP_MOVE_H_ */
