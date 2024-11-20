#ifndef _INTERPRET_COMMAND_H_
#define _INTERPRET_COMMAND_H_

#include <memory>

#include "Command/ICommand.h"
#include "IoC/IoC.h"
#include "EndPoint/MessageAdapter.h"
#include "Common/QueueCommand.h"

extern IoC* ioc;
// Задача в нужную очередь(объекта) положить нужную команду
class InterpretCommand : public ICommand
{
public:

	InterpretCommand(std::shared_ptr<IMessagable> message_,  size_t scopeIdCur_, std::shared_ptr<QueueCommand> queue_) 
		: massagable(message_)
		, scopeIdCur(scopeIdCur_)
		, queue(queue_)
	{}	

	virtual ~InterpretCommand() {}

	void Execute()
	{
        // Должен добавить конкретную команду в игру Game Command TODO проверить!!!!!!!
        ioc->Resolve<ICommand_Ptr>("Scopes.Current", &scopeIdCur);
        // TODO доделать !!!!!!!!!
        ICommand_Ptr cmdCur = ioc->Resolve<ICommand_Ptr>(massagable->getTypeCommand(), massagable);
	}

	std::string GetType()
	{
		return "InterpretCommand";
	}

private:
	std::shared_ptr<IMessagable>				massagable;
	size_t									    scopeIdCur;
	std::shared_ptr<QueueCommand>				queue;
};

#endif /* _INTERPRET_COMMAND_H_ */
