#ifndef _MOVE_COMMAND_PLUGIN_H_
#define _MOVE_COMMAND_PLUGIN_H_

#include <string>

#include "IoC/IoCGlobal.h" // TODO сделать это как-то по-другому
#include "Common/IPlugin.h"
#include "Common/UObject.h"
#include "ClassFunctionMove.h"
#include "Common/SpaceShip.h"
#include "inputPlugins/MoveCommandPlugin/MovableAdapter.h"

// Доступные команды 
// TODO !!!!!!!!!!!! описать !!!!!!!!!!!
// "IMovable.Location" - 


// "IMovable.Location.Set" - 

// "IMovable.Velocity"
// "Command.Move"


class MoveCommandPlugin: public IPlugin
{
public:

	void Load() override
	{
		SpaceShip x;
		UObject_Ptr obj = std::make_shared<SpaceShip>(x);
		std::function<std::vector<int>(UObject_Ptr)> funcLoc = &ClassFunctionMove::IMovableLocationFunc;
		ioc.Resolve<ICommand_Ptr, std::vector<int>, std::string, std::function<std::vector<int>(UObject_Ptr)> >(
			"IoC.Register", 
			"IMovable.Location", 
			funcLoc, obj);

		std::function<void(UObject_Ptr obj, boost::any value)> funcLocSet = &ClassFunctionMove::IMovableLocationSetFunc;
		ioc.Resolve<ICommand_Ptr, void, std::string, std::function<void(UObject_Ptr obj, boost::any value)> >(
			"IoC.Register", 
			"IMovable.Location.Set", 
			funcLocSet, obj);

		std::function<std::vector<int>(UObject_Ptr obj)> funcVel = &ClassFunctionMove::IMovableVelocityFunc;
		ioc.Resolve<ICommand_Ptr, std::vector<int>, std::string, std::function<std::vector<int>(UObject_Ptr obj)> >(
			"IoC.Register", 
			"IMovable.Velocity", 
			funcVel, obj);

		std::function<std::shared_ptr<IMovable>(UObject_Ptr obj)> funcAdapterIMovable = &ClassFunctionMove::AdaptersIMovableFunc;
		ioc.Resolve<ICommand_Ptr, std::shared_ptr<IMovable>, std::string, std::function<std::shared_ptr<IMovable>(UObject_Ptr obj)> >(
			"IoC.Register",
			"Adapters.IMovable",
			funcAdapterIMovable, obj);

		std::function<ICommand_Ptr(UObject_Ptr obj)> funcCommandMove = &ClassFunctionMove::CommandMoveFunc;
		ioc.Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(UObject_Ptr obj)> >(
			"IoC.Register",
			"Command.Move",
			funcCommandMove, obj);
	}

	std::string GetType()
	{
		return "MoveCommandPlugin";
	}
};

#endif /* _MOVE_COMMAND_PLUGIN_H_ */
