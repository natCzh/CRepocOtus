#include <functional>
#include <boost/bind.hpp>

#include "ShotCommandPlugin.h"

#include "ClassFunctionShot.h"
#include "../../Common/SpaceShip.h"
#include "ShotAdapter.h"
#include "../../Command/ICommand.h"
#include "../../CommonLib/objectAble/IShotable.h"

#include "../../service/TourneyService/IoCGlobal.h"

void ShotCommandPlugin::InitPlugin(IoC* iocCur)
{ ioc = iocCur; }

void ShotCommandPlugin::Load()
{
	SpaceShip x;
	UObject_Ptr obj = std::make_shared<SpaceShip>(x);
    std::function<int(UObject_Ptr)> funcNumberShot = boost::bind(&ClassFunctionShot::IShotableNumberShotFunc, &classFunctionShot, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, int, std::string, std::function<int(UObject_Ptr)> >(
		"IoC.Register", 
		"IShotable.NumberShot", 
        funcNumberShot, obj)->Execute();

    int value = 1;
    std::function<ICommand_Ptr(UObject_Ptr, int value)> funcShotActSet = boost::bind(&ClassFunctionShot::IShotableShotActSetFunc, &classFunctionShot, std::placeholders::_1, std::placeholders::_2);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(UObject_Ptr, int value)> >(
		"IoC.Register", 
		"IShotable.ShotAct.Set", 
        funcShotActSet, obj, value)->Execute();

    std::function<ICommand_Ptr(UObject_Ptr, int value)> funcNumberShotSet = boost::bind(&ClassFunctionShot::IShotableNumberShotSetFunc, &classFunctionShot, std::placeholders::_1, std::placeholders::_2);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(UObject_Ptr, int value)> >(
		"IoC.Register", 
		"IShotable.NumberShot.Set", 
        funcNumberShotSet, obj, value)->Execute();

    std::function<std::shared_ptr<IShotable>(UObject_Ptr obj)> funcAdapterIShotable = boost::bind(&ClassFunctionShot::AdaptersIShotableFunc, &classFunctionShot, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, std::shared_ptr<IShotable>, std::string, std::function<std::shared_ptr<IShotable>(UObject_Ptr obj)> >(
		"IoC.Register",
		"Adapters.IShotable",
        funcAdapterIShotable, obj)->Execute();

    std::function<ICommand_Ptr(UObject_Ptr obj)> funcCommandShot = boost::bind(&ClassFunctionShot::CommandShotFunc, &classFunctionShot, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(UObject_Ptr obj)> >(
		"IoC.Register",
		"Command.Shot",
        funcCommandShot, obj)->Execute();
}

std::string ShotCommandPlugin::GetType()
{
	return "ShotCommandPlugin";
}
