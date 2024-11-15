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
    /*SpaceShip x;
	UObject_Ptr obj = std::make_shared<SpaceShip>(x);
    std::function<std::vector<int>(UObject_Ptr)> funcLoc = boost::bind(&ClassFunctionMove::IMovableLocationFunc, &classFunctionMove, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, std::vector<int>, std::string, std::function<std::vector<int>(UObject_Ptr)> >(
		"IoC.Register", 
		"IMovable.Location", 
        funcLoc, obj)->Execute();*/


    std::function<int(void)> funcLoc = boost::bind(&ClassFunctionMove::IMovableLocationFunc_Test, &classFunctionMove);
    ioc->Resolve<ICommand_Ptr, void, std::string, std::function<int()> >(
           "IoC.Register",
           "IMovable.Location",
           funcLoc)->Execute();

    int s = 0;
    int ds = ioc->Resolve<int>("IMovable.Location");
    s += 1;


    /*boost::any valueNew;
	std::function<void(UObject_Ptr obj, boost::any value)> funcLocSet = &ClassFunctionMove::IMovableLocationSetFunc;
    ioc->Resolve<ICommand_Ptr, void, std::string, std::function<void(UObject_Ptr obj, boost::any value)> >(
        "IoC.Register",
        "IMovable.Location.Set",
        funcLocSet, obj, valueNew)->Execute();

	std::function<std::vector<int>(UObject_Ptr obj)> funcVel = &ClassFunctionMove::IMovableVelocityFunc;
    ioc->Resolve<ICommand_Ptr, std::vector<int>, std::string, std::function<std::vector<int>(UObject_Ptr obj)> >(
		"IoC.Register", 
		"IMovable.Velocity", 
        funcVel, obj)->Execute();

	std::function<std::shared_ptr<IMovable>(UObject_Ptr obj)> funcAdapterIMovable = &ClassFunctionMove::AdaptersIMovableFunc;
    ioc->Resolve<ICommand_Ptr, std::shared_ptr<IMovable>, std::string, std::function<std::shared_ptr<IMovable>(UObject_Ptr obj)> >(
		"IoC.Register",
		"Adapters.IMovable",
        funcAdapterIMovable, obj)->Execute();

	std::function<ICommand_Ptr(UObject_Ptr obj)> funcCommandMove = &ClassFunctionMove::CommandMoveFunc;
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(UObject_Ptr obj)> >(
		"IoC.Register",
		"Command.Move",
        funcCommandMove, obj)->Execute();*/
}

std::string MoveCommandPlugin::GetType()
{
	return "MoveCommandPlugin";
}

/*void InitPlugin(IoC* ioc)
{
	
}*/
