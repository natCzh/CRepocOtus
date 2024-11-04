#ifndef _COMMAND_INTERPRET_COMMAND_H_
#define _COMMAND_INTERPRET_COMMAND_H_

#include <memory>

#include "IoC/IoCGlobal.h"
#include "Command/ICommand.h"
#include "Common/QueueCommand.h"
#include "Exception/InterpretCommandException.h"

class CommandInterpretCommand_StartMove: public ICommand
{
public:

	CommandInterpretCommand_StartMove(std::shared_ptr<IMessagable> messagable_, std::shared_ptr<QueueCommand> queue_)
		: messagable(messagable_)
		, queue(queue_)
	{}

	void Execute() override
	{
		// так как в Interpret уже выставлен scope для нужного объекта, мы просто получаем нужный объект
		std::shared_ptr<UObject> curObject = ioc.Resolve<std::shared_ptr<UObject> >(
			"GameItems");
		ioc.Resolve<ICommand_Ptr>(
			"CommandInterpret.PrepareForMove",
			curObject,
			messagable);

		ICommand_Ptr cmd = ioc.Resolve<ICommand_Ptr>("Move");
		queue->Push(cmd);
	}

	std::string GetType() override
	{
		return "CommandInterpretCommand_StartMove";
	}

protected:
	std::shared_ptr<IMessagable>						messagable;
	std::shared_ptr<QueueCommand>						queue;
};

class CommandInterpretPrepareForMove : public ICommand
{
public:

	CommandInterpretPrepareForMove(std::shared_ptr<UObject> obj_, std::shared_ptr<std::map<std::string, boost::any> > messagable_)
		: obj(obj_)
		, messagable(messagable_)
	{}

	void Execute() override
	{
		auto valVelX = std::find(messagable->begin(), messagable->end(), "velocity_x");
		if (valVelX == messagable->end())
			InterpretCommandException("UObject messagable - velocity_x isn't exist");
		obj->setProperty("velocity_x", valVelX);
		auto valVelY = std::find(messagable->begin(), messagable->end(), "velocity_y");
		if (valVelY == messagable->end())
			InterpretCommandException("UObject messagable - velocity_y isn't exist");
		obj->setProperty("velocity_y", valVelY);
	}

	std::string GetType() override
	{
		return "CommandInterpret.PrepareForMove";
	}

protected:
	std::shared_ptr<UObject>									obj;
	std::shared_ptr<std::map<std::string, boost::any> >			messagable;
};

class CommandInterpretCommand_StopMove: public ICommand
{
public:

	CommandInterpretCommand_StopMove(std::shared_ptr<IMessagable> messagable_)
		: messagable(messagable_)
	{}

	void Execute() override
	{
		std::shared_ptr<UObject> curObject = ioc.Resolve<std::shared_ptr<UObject> >(
		 	"GameItems");
		ioc.Resolve<ICommand_Ptr>(
			"CommandInterpret.PrepareForStopMove",
			curObject);
		 
		ICommand_Ptr cmd = ioc.Resolve<ICommand_Ptr>("MoveStop");
		//std::shared_ptr<QueueCommand> queue = ioc.Resolve<std::shared_ptr<QueueCommand> >("Game.Queue");
		// queue->Push(cmd);
	}

	std::string GetType() override
	{
		return "CommandInterpretCommand_StopMove";
	}

protected:
	std::shared_ptr<IMessagable>						messagable;
};

class CommandInterpretPrepareForStopMove : public ICommand
{
public:

	CommandInterpretPrepareForStopMove(std::shared_ptr<UObject> obj_)
		: obj(obj_)
	{}

	void Execute() override
	{
		boost::any valVelX = 0;
		obj->setProperty("velocity_x", valVelX);
		obj->setProperty("velocity_y", valVelX);
	}

	std::string GetType() override
	{
		return "CommandInterpret.PrepareForStopMove";
	}

protected:
	std::shared_ptr<UObject>									obj;
};

class CommandInterpretCommand_Shot: public ICommand
{
public:

	CommandInterpretCommand_Shot(std::shared_ptr<IMessagable> messagable_, std::shared_ptr<QueueCommand> queue_)
		: messagable(messagable_)
		, queue(queue_)
	{}

	void Execute() override
	{
		std::shared_ptr<UObject> curObject = ioc.Resolve<std::shared_ptr<UObject> >(
			"GameItems");
		ioc.Resolve<ICommand_Ptr>(
			"CommandInterpret.PrepareForShot",
			curObject,
			messagable);

		ICommand_Ptr cmd = ioc.Resolve<ICommand_Ptr>("Shot");
		queue->Push(cmd);
	}

	std::string GetType() override
	{
		return "CommandInterpretCommand_Shot";
	}

protected:
	std::shared_ptr<IMessagable>						messagable;
	std::shared_ptr<QueueCommand>						queue;
};

// TODO !!!!! тут может быть проверка выстрела
class CommandInterpretPrepareForShot : public ICommand
{
public:

	CommandInterpretPrepareForShot(std::shared_ptr<UObject> obj_)
		: obj(obj_)
	{}

	void Execute() override
	{
	}

	std::string GetType() override
	{
		return "CommandInterpret.PrepareForShot";
	}

protected:
	std::shared_ptr<UObject>									obj;
};


#endif /* _COMMAND_INTERPRET_COMMAND_H_ */
