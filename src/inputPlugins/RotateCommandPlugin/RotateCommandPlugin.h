#ifndef _ROTATE_COMMAND_PLUGIN_H_
#define _ROTATE_COMMAND_PLUGIN_H_

#include <string>

#include "IoC/IoCGlobal.h" // TODO ������� ��� ���-�� ��-�������
#include "Common/IPlugin.h"
#include "Common/UObject.h"
#include "Common/SpaceShip.h"
#include "inputPlugins/RotateCommandPlugin/ClassFunctionRotate.h"

// ��������� ������� 
// TODO !!!!!!!!!!!! ������� !!!!!!!!!!!
// "IRotable.Direction"
// "IRotable.Direction.Set"
// "Adapters.IRotable"
// "Command.Rotate"

class RotateCommandPlugin: public IPlugin
{
public:

	void Load() override
	{
		SpaceShip x;
		UObject_Ptr obj = std::make_shared<SpaceShip>(x);
		std::function<int(UObject_Ptr)> funcDirect = &ClassFunctionRotate::IRotableDirectionFunc;
		ioc.Resolve<ICommand_Ptr, int, std::string, std::function<int(UObject_Ptr)> >(
			"IoC.Register", 
			"IRotable.Direction", 
			funcDirect, obj);

		std::function<void(UObject_Ptr obj, boost::any value)> funcDirSet = &ClassFunctionRotate::IRotableDirectionSetFunc;
		ioc.Resolve<ICommand_Ptr, void, std::string, std::function<void(UObject_Ptr obj, boost::any value)> >(
			"IoC.Register", 
			"IRotable.Direction.Set", 
			funcDirSet, obj);

		std::function<int(UObject_Ptr obj)> funcDirAngular = &ClassFunctionRotate::IRotableDirectionAngularFunc;
		ioc.Resolve<ICommand_Ptr, int, std::string, std::function<int(UObject_Ptr obj)> >(
			"IoC.Register", 
			"IRotable.DirectionAngular", 
			funcDirAngular, obj);

		std::function<int(UObject_Ptr obj)> funcDirNumber = &ClassFunctionRotate::IRotableDirectionNumberFunc;
		ioc.Resolve<ICommand_Ptr, int, std::string, std::function<int(UObject_Ptr obj)> >(
			"IoC.Register", 
			"IRotable.DirectionNumber", 
			funcDirNumber, obj);

		std::function<std::shared_ptr<IRotable>(UObject_Ptr obj)> funcAdapterIRotable = &ClassFunctionRotate::AdaptersIRotableFunc;
		ioc.Resolve<ICommand_Ptr, std::shared_ptr<IRotable>, std::string, std::function<std::shared_ptr<IRotable>(UObject_Ptr obj)> >(
			"IoC.Register",
			"Adapters.IRotable",
			funcAdapterIRotable, obj);

		std::function<ICommand_Ptr(UObject_Ptr obj)> funcCommandRotate = &ClassFunctionRotate::CommandRotateFunc;
		ioc.Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(UObject_Ptr obj)> >(
			"IoC.Register",
			"Command.Rotate",
			funcCommandRotate, obj);
	}

	std::string GetType()
	{
		return "RotateCommandPlugin";
	}
};

#endif /* _ROTATE_COMMAND_PLUGIN_H_ */
