#include <functional>
#include <boost/bind.hpp>

#include "RotateCommandPlugin.h"

#include "ClassFunctionRotate.h"
#include "../../Common/SpaceShip.h"
#include "RotableAdapter.h"
#include "../../Command/ICommand.h"
#include "../../CommonLib/objectAble/IRotable.h"

#include "../../service/TourneyService/IoCGlobal.h"

void RotateCommandPlugin::InitPlugin(IoC* iocCur)
{ ioc = iocCur; }


void RotateCommandPlugin::Load()
{
	SpaceShip x;
	UObject_Ptr obj = std::make_shared<SpaceShip>(x);
    std::function<int(UObject_Ptr)> funcDirect = boost::bind(&ClassFunctionRotate::IRotableDirectionFunc, &classFunctionRotate, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, int, std::string, std::function<int(UObject_Ptr)> >(
		"IoC.Register", 
		"IRotable.Direction", 
        funcDirect, obj)->Execute();

    int value = 1;
    std::function<ICommand_Ptr(UObject_Ptr obj, int value)> funcDirSet = boost::bind(&ClassFunctionRotate::IRotableDirectionSetFunc, &classFunctionRotate, std::placeholders::_1, std::placeholders::_2);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(UObject_Ptr obj, int value)> >(
		"IoC.Register", 
		"IRotable.Direction.Set", 
        funcDirSet, obj, value)->Execute();

    std::function<int(UObject_Ptr obj)> funcDirAngular = boost::bind(&ClassFunctionRotate::IRotableDirectionAngularFunc, &classFunctionRotate, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, int, std::string, std::function<int(UObject_Ptr obj)> >(
		"IoC.Register", 
		"IRotable.DirectionAngular", 
        funcDirAngular, obj)->Execute();

    std::function<int(UObject_Ptr obj)> funcDirNumber = boost::bind(&ClassFunctionRotate::IRotableDirectionNumberFunc, &classFunctionRotate, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, int, std::string, std::function<int(UObject_Ptr obj)> >(
		"IoC.Register", 
		"IRotable.DirectionNumber", 
        funcDirNumber, obj)->Execute();

    std::function<std::shared_ptr<IRotable>(UObject_Ptr obj)> funcAdapterIRotable = boost::bind(&ClassFunctionRotate::AdaptersIRotableFunc, &classFunctionRotate, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, std::shared_ptr<IRotable>, std::string, std::function<std::shared_ptr<IRotable>(UObject_Ptr obj)> >(
		"IoC.Register",
		"Adapters.IRotable",
        funcAdapterIRotable, obj)->Execute();

    std::function<ICommand_Ptr(UObject_Ptr obj)> funcCommandRotate = boost::bind(&ClassFunctionRotate::CommandRotateFunc, &classFunctionRotate, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(UObject_Ptr obj)> >(
		"IoC.Register",
		"Command.Rotate",
        funcCommandRotate, obj)->Execute();
}

std::string RotateCommandPlugin::GetType()
{
	return "RotateCommandPlugin";
}
