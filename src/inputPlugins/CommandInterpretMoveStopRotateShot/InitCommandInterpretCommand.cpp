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
        funcPrepareForMove, obj, messagable)->Execute();

    std::shared_ptr<QueueCommand> queue;
    std::function<ICommand_Ptr(IMessagable_Ptr, std::shared_ptr<QueueCommand>)> funcInterpretStartMove = boost::bind(&ClassFunctionInitCommandInterpret::CommandInterpretCommandStartMove, &classFunction, std::placeholders::_1, std::placeholders::_2);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(IMessagable_Ptr, std::shared_ptr<QueueCommand>)> >(
        "IoC.Register",
        "CommandInterpret.StartMove",
        funcInterpretStartMove, messagable, queue)->Execute();

    std::function<ICommand_Ptr(UObject_Ptr)> funcPrepareForStopMove = boost::bind(&ClassFunctionInitCommandInterpret::CommandPrepareForStopMove, &classFunction, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(UObject_Ptr)> >(
        "IoC.Register",
        "CommandInterpret.PrepareForStopMove",
        funcPrepareForStopMove, obj)->Execute();

    std::function<ICommand_Ptr(IMessagable_Ptr)> funcInterpretStopMove = boost::bind(&ClassFunctionInitCommandInterpret::CommandInterpretCommandStopMove, &classFunction, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(IMessagable_Ptr)> >(
        "IoC.Register",
        "CommandInterpret.StopMove",
        funcInterpretStopMove, messagable)->Execute();

    int x = 0;
    std::function<ICommand_Ptr(UObject_Ptr, int)> funcPrepareForRotate = boost::bind(&ClassFunctionInitCommandInterpret::CommandPrepareForRotate, &classFunction, std::placeholders::_1, std::placeholders::_2);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(UObject_Ptr, int)> >(
        "IoC.Register",
        "CommandInterpret.PrepareForRotate",
        funcPrepareForRotate, obj, x)->Execute();

    std::function<ICommand_Ptr(IMessagable_Ptr, std::shared_ptr<QueueCommand> queue)> funcInterpretRotate = boost::bind(&ClassFunctionInitCommandInterpret::CommandInterpretCommandRotate, &classFunction, std::placeholders::_1, std::placeholders::_2);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(IMessagable_Ptr, std::shared_ptr<QueueCommand> queu)> >(
        "IoC.Register",
        "CommandInterpret.Rotate",
        funcInterpretRotate, messagable, queue)->Execute();

    std::function<ICommand_Ptr(UObject_Ptr)> funcPrepareForShot = boost::bind(&ClassFunctionInitCommandInterpret::CommandPrepareForShot, &classFunction, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(UObject_Ptr)> >(
           "IoC.Register",
           "CommandInterpret.PrepareForShot",
           funcPrepareForShot, obj)->Execute();

    std::function<ICommand_Ptr(IMessagable_Ptr, std::shared_ptr<QueueCommand> queue)> funcInterpretShot = boost::bind(&ClassFunctionInitCommandInterpret::CommandInterpretCommandShot, &classFunction, std::placeholders::_1, std::placeholders::_2);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(IMessagable_Ptr, std::shared_ptr<QueueCommand> queu)> >(
           "IoC.Register",
           "CommandInterpret.Shot",
           funcInterpretShot, messagable, queue)->Execute();
}

std::string InitCommandInterpretCommand::GetType()
{
    return "InitCommandInterpretCommand";
}
