#ifndef _INTERPRET_COMMAND_H_
#define _INTERPRET_COMMAND_H_

#include <memory>

#include "Command/ICommand.h"
#include "IoC/IoCGlobal.h"
#include "EndPoint/MessageAdapter.h"

// Задача в нужную очередь(объекта) положить нужную команду
class InterpretCommand : public ICommand
{
public:

	InterpretCommand(std::shared_ptr<Message> message_) 
		: massagable(message_)
	{}	

	virtual ~InterpretCommand() {}

	void Execute()
	{
		ioc.Resolve<ICommand>(massagable.getTypeCommand(), massagable);
	}

	std::string GetType()
	{
		return "InterpretCommand";
	}

private:
	MessageAdapter				massagable;

};

#endif /* _INTERPRET_COMMAND_H_ */
