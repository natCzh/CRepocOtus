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

	InterpretCommand(std::shared_ptr<IMessagable> message_,  size_t scopeIdCur_) 
		: massagable(message_)
		, scopeIdCur(scopeIdCur_)
	{}	

	virtual ~InterpretCommand() {}

	void Execute()
	{
		ioc.Resolve<ICommand_Ptr>("Scopes.Current", &scopeIdCur); // TODO тут должна быть команда переделать !!!!!!!!!!!!

		ICommand_Ptr cmd = ioc.Resolve<ICommand_Ptr>(massagable->getTypeCommand(), massagable);
	}

	std::string GetType()
	{
		return "InterpretCommand";
	}

private:
	std::shared_ptr<IMessagable>				massagable;
	size_t									    scopeIdCur;
};

#endif /* _INTERPRET_COMMAND_H_ */
