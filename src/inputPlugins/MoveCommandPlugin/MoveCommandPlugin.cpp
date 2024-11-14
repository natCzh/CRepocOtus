#include <functional>

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
	std::function<std::vector<int>(UObject_Ptr)> funcLoc = &ClassFunctionMove::IMovableLocationFunc;
    ioc->Resolve<ICommand_Ptr, std::vector<int>, std::string, std::function<std::vector<int>(UObject_Ptr)> >(
		"IoC.Register", 
		"IMovable.Location", 
		funcLoc, obj);

	boost::any valueNew;
	std::function<void(UObject_Ptr obj, boost::any value)> funcLocSet = &ClassFunctionMove::IMovableLocationSetFunc;
    ioc->Resolve<ICommand_Ptr, void, std::string, std::function<void(UObject_Ptr obj, boost::any value)> >(
		"IoC.Register", 
		"IMovable.Location.Set", 
		funcLocSet, obj, valueNew);

	std::function<std::vector<int>(UObject_Ptr obj)> funcVel = &ClassFunctionMove::IMovableVelocityFunc;
    ioc->Resolve<ICommand_Ptr, std::vector<int>, std::string, std::function<std::vector<int>(UObject_Ptr obj)> >(
		"IoC.Register", 
		"IMovable.Velocity", 
		funcVel, obj);

	std::function<std::shared_ptr<IMovable>(UObject_Ptr obj)> funcAdapterIMovable = &ClassFunctionMove::AdaptersIMovableFunc;
    ioc->Resolve<ICommand_Ptr, std::shared_ptr<IMovable>, std::string, std::function<std::shared_ptr<IMovable>(UObject_Ptr obj)> >(
		"IoC.Register",
		"Adapters.IMovable",
		funcAdapterIMovable, obj);

	std::function<ICommand_Ptr(UObject_Ptr obj)> funcCommandMove = &ClassFunctionMove::CommandMoveFunc;
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(UObject_Ptr obj)> >(
		"IoC.Register",
		"Command.Move",
		funcCommandMove, obj);
}

std::string MoveCommandPlugin::GetType()
{
	return "MoveCommandPlugin";
}

/*void InitPlugin(IoC* ioc)
{
	
}*/
