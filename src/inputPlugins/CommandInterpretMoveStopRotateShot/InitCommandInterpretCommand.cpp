#include <functional>
#include <boost/bind.hpp>

#include "InitCommandInterpretCommand.h"

#include "IoC/IoC.h"

extern IoC* ioc;
void InitCommandInterpretCommand::Execute()
{

    UObject_Ptr obj;
    IMessagable_Ptr messagable;
    std::function<ICommand_Ptr(UObject_Ptr, IMessagable_Ptr)> funcPrepareForMove = boost::bind(&ClassFunctionInitCommandInterpret::CommandPrepareForMove, &classFunction, std::placeholders::_1, std::placeholders::_2);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(UObject_Ptr, IMessagable_Ptr)> >(
        "IoC.Register",
        "CommandInterpret.PrepareForMove",
        funcPrepareForMove, obj, messagable);

    std::shared_ptr<QueueCommand> queue;
    std::function<ICommand_Ptr(IMessagable_Ptr, std::shared_ptr<QueueCommand>)> funcInterpretStartMove = boost::bind(&ClassFunctionInitCommandInterpret::CommandInterpretCommandStartMove, &classFunction, std::placeholders::_1, std::placeholders::_2);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(IMessagable_Ptr, std::shared_ptr<QueueCommand>)> >(
        "IoC.Register",
        "CommandInterpret.StartMove",
        funcInterpretStartMove, messagable, queue);
}

std::string InitCommandInterpretCommand::GetType()
{
    return "InitCommandInterpretCommand";
}
