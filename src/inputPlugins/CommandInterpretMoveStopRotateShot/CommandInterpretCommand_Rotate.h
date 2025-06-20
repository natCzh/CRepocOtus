#ifndef _COMMAND_INTERPRET_COMMAND_ROTATE_H_
#define _COMMAND_INTERPRET_COMMAND_ROTATE_H_

#include <memory>
#include <unordered_map>
#include "boost/any.hpp"

#include "IoC/IoC.h"
#include "CommonLib/IMessagable.h"
#include "Common/QueueCommand.h"
#include "CommonLib/UObject.h"
#include "Exception/InterpretCommandException.h"

extern IoC* ioc;
class CommandInterpretCommand_Rotate: public ICommand
{
public:


    /// @param[in] directionRotate - направление поворота 1 - по часовой, -1 - против часовой
    CommandInterpretCommand_Rotate(IMessagable_Ptr messagable_, std::shared_ptr<QueueCommand> queue_)
		: messagable(messagable_)
        , queue(queue_)
	{}

	void Execute() override
	{
        // так как в Interpret уже выставлен scope для нужной игры, мы просто получаем нужный объект
        std::unordered_map<unsigned long long, UObject_Ptr> curVectObject = ioc->Resolve<std::unordered_map<unsigned long long, UObject_Ptr> >(
            "GameItems");
        UObject_Ptr curObject = curVectObject.find(messagable->getIdObject())->second;

        std::map<std::string, boost::any> allProperties = messagable->getProperties();
        auto iter = allProperties.find("directionAngular");
        if (iter == allProperties.end())
            throw InterpretCommandException("Messagable getProperties - directionAngular isn't exist");

        int directionRotate = boost::any_cast<int>(iter->second);
        ioc->Resolve<ICommand_Ptr>(
            "CommandInterpret.PrepareForRotate",
            curObject, directionRotate)->Execute();

        ICommand_Ptr cmd = ioc->Resolve<ICommand_Ptr>("Command.Rotate", curObject);
        queue->Push(cmd);
	}

	std::string GetType() override
	{
        return "CommandInterpret.Rotate";
	}

protected:
    IMessagable_Ptr             						messagable;
    std::shared_ptr<QueueCommand>                       queue;
};

#endif /* _COMMAND_INTERPRET_COMMAND_ROTATE_H_ */
