#include "inputPlugins/ShotCommandPlugin/ShotCommandPlugin.h"

#include "IoC/IoCGlobal.h" // TODO сделать это как-то по-другому
#include "Common/UObject.h"
#include "Common/SpaceShip.h"
#include "inputPlugins/ShotCommandPlugin/ClassFunctionShot.h"

void ShotCommandPlugin::Load()
{
	SpaceShip x;
	UObject_Ptr obj = std::make_shared<SpaceShip>(x);
	std::function<int(UObject_Ptr)> funcNumberShot = &ClassFunctionShot::IShotableNumberShotFunc;
	ioc.Resolve<ICommand_Ptr, int, std::string, std::function<int(UObject_Ptr)> >(
		"IoC.Register", 
		"IShotable.NumberShot", 
		funcNumberShot, obj);

	std::function<void(UObject_Ptr, boost::any value)> funcShotActSet = &ClassFunctionShot::IShotableShotActSetFunc;
	ioc.Resolve<ICommand_Ptr, void, std::string, std::function<void(UObject_Ptr, boost::any value)> >(
		"IoC.Register", 
		"IShotable.ShotAct.Set", 
		funcShotActSet, obj);

	std::function<void(UObject_Ptr, boost::any value)> funcNumberShotSet = &ClassFunctionShot::IShotableNumberShotSetFunc;
	ioc.Resolve<ICommand_Ptr, void, std::string, std::function<void(UObject_Ptr, boost::any value)> >(
		"IoC.Register", 
		"IShotable.NumberShot.Set", 
		funcNumberShotSet, obj);

	std::function<std::shared_ptr<IShotable>(UObject_Ptr obj)> funcAdapterIShotable = &ClassFunctionShot::AdaptersIShotableFunc;
	ioc.Resolve<ICommand_Ptr, std::shared_ptr<IShotable>, std::string, std::function<std::shared_ptr<IShotable>(UObject_Ptr obj)> >(
		"IoC.Register",
		"Adapters.IShotable",
		funcAdapterIShotable, obj);

	std::function<ICommand_Ptr(UObject_Ptr obj)> funcCommandShot = &ClassFunctionShot::CommandShotFunc;
	ioc.Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(UObject_Ptr obj)> >(
		"IoC.Register",
		"Command.Shot",
		funcCommandShot, obj);
}

std::string ShotCommandPlugin::GetType()
{
	return "ShotCommandPlugin";
}
