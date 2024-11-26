#ifndef _INTERPRET_COMMAND_H_
#define _INTERPRET_COMMAND_H_

#include <memory>

#include "Command/ICommand.h"
#include "IoC/IoC.h"
#include "CommonLib/IMessagable.h"
#include "Common/QueueCommand.h"
#include "CommonLib/UObject.h"

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
        ioc->Resolve<void>("Scopes.Current.SetId", scopeIdCur);
        unsigned int idObj = massagable->getIdObject();
        ICommand_Ptr cmd;
        std::unordered_map<unsigned long long, UObject> objs = ioc->Resolve<std::unordered_map<unsigned long long, UObject> >("GameItems");
        UObject_Ptr obj = std::make_shared<UObject>(objs.find(idObj).second);
        if (std::strcmp(massagable->getTypeCommand().c_str(), "Command.MoveLongOperation") == 0) // TODO тут потом проверять имя на LongOperation автоматом
            cmd = ioc->Resolve<ICommand_Ptr>(massagable->getTypeCommand(), size_t(idObj), queue);
        else
            cmd = ioc->Resolve<ICommand_Ptr>(massagable->getTypeCommand(), obj);

        queue->Push(cmd);
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
