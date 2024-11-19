#include <functional>
#include <boost/bind.hpp>

#include "MoveCommandPlugin.h"

#include "ClassFunctionMove.h"
#include "../../Common/SpaceShip.h"
#include "MovableAdapter.h"
#include "../../Command/ICommand.h"
#include "../../CommonLib/objectAble/IMovable.h"

#include "../../service/TourneyService/IoCGlobal.h"

void MoveCommandPlugin::InitPlugin(IoC* iocCur)
{ ioc = iocCur; }


void MoveCommandPlugin::Load()
{
    SpaceShip x;
	UObject_Ptr obj = std::make_shared<SpaceShip>(x);
    std::function<std::vector<int>(UObject_Ptr)> funcLoc = boost::bind(&ClassFunctionMove::IMovableLocationFunc, &classFunctionMove, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, std::vector<int>, std::string, std::function<std::vector<int>(UObject_Ptr)> >(
		"IoC.Register", 
		"IMovable.Location", 
        funcLoc, obj)->Execute();

    std::vector<int> Vel(2, 0);
    std::function<ICommand_Ptr(UObject_Ptr obj, std::vector<int> value)> funcLocSet = boost::bind(&ClassFunctionMove::IMovableLocationSetFunc, &classFunctionMove, std::placeholders::_1, std::placeholders::_2);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(UObject_Ptr obj, std::vector<int> value)> >(
        "IoC.Register",
        "IMovable.Location.Set",
        funcLocSet, obj, Vel)->Execute();

    std::function<std::vector<int>(UObject_Ptr obj)> funcVel = boost::bind(&ClassFunctionMove::IMovableVelocityFunc, &classFunctionMove, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, std::vector<int>, std::string, std::function<std::vector<int>(UObject_Ptr obj)> >(
		"IoC.Register", 
		"IMovable.Velocity", 
        funcVel, obj)->Execute();

    std::function<std::shared_ptr<IMovable>(UObject_Ptr obj)> funcAdapterIMovable = boost::bind(&ClassFunctionMove::AdaptersIMovableFunc, &classFunctionMove, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, std::shared_ptr<IMovable>, std::string, std::function<std::shared_ptr<IMovable>(UObject_Ptr obj)> >(
		"IoC.Register",
		"Adapters.IMovable",
        funcAdapterIMovable, obj)->Execute();

    std::function<ICommand_Ptr(UObject_Ptr obj)> funcCommandMove = boost::bind(&ClassFunctionMove::CommandMoveFunc, &classFunctionMove, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(UObject_Ptr obj)> >(
		"IoC.Register",
		"Command.Move",
        funcCommandMove, obj)->Execute();

    size_t idObj = 0;
    std::function<ICommand_Ptr(size_t idObj)> funcCommandMovement = boost::bind(&ClassFunctionMove::CommandMovementFunc, &classFunctionMove, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(size_t idObj)> >(
        "IoC.Register",
        "Command.Movement",
        funcCommandMovement, idObj)->Execute();

    std::shared_ptr<QueueCommand> qCommand = std::make_shared<QueueCommand>(100);
    std::function<ICommand_Ptr(size_t idObj, std::shared_ptr<QueueCommand> qCommand)> funcCommandMoveLongOperation = boost::bind(&ClassFunctionMove::CommandMoveLongOperationFunc, &classFunctionMove, std::placeholders::_1, std::placeholders::_2);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(size_t idObj, std::shared_ptr<QueueCommand> qCommand)> >(
        "IoC.Register",
        "Command.MoveLongOperation",
        funcCommandMoveLongOperation, idObj, qCommand)->Execute();
}

std::string MoveCommandPlugin::GetType()
{
	return "MoveCommandPlugin";
}
