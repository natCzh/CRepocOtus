#ifndef _INTERPRET_COMMAND_H_
#define _INTERPRET_COMMAND_H_

#include <memory>

#include "Command/ICommand.h"
#include "IoC/IoCGlobal.h"
#include "EndPoint/MessageAdapter.h"

// «адача в нужную очередь(объекта) положить нужную команду
class InterpretCommand : public ICommand
{
public:

	InterpretCommand(std::shared_ptr<IMessagable> message_) 
		: massagable(message_)
	{}	

	virtual ~InterpretCommand() {}

	void Execute()
	{


		// тут надо из IOC и massagable получить ид объекта, те указатель на нее
		ICommand_Ptr cmd = ioc.Resolve<ICommand_Ptr>(massagable->getTypeCommand(), massagable);
		// эту команду нужно положить в очередь, исп ioc и команду добавить в очередь, те в IOC должна хранитс€ очередь

	}

	std::string GetType()
	{
		return "InterpretCommand";
	}

private:
	std::shared_ptr<IMessagable>				massagable;

};

#endif /* _INTERPRET_COMMAND_H_ */
