#ifndef _STATES_QUEUE_PROCESSING_H_
#define _STATES_QUEUE_PROCESSING_H_

#include <memory>

#include "ICommand.h"
#include "QueueCommand.h"
#include "ICommandStatesQueueProcessing.h"
#include "Command.h"

///////////////////////////////////////////////////////////////
///////////////// Конкретные состояния

// Пустое состояние - завершение работы потока
/*class EmptyStatesQueueProcessing: public ICommandStatesQueueProcessing
{
public:
	void handle(queueProcessing *m)
	{
		// тут должен быть напрмиер эксепшен,чтобы выйти из потока
	}

	void pushCommand(ICommand_Ptr commandCur)
	{
		// ничего не происходит
	}
};*/

class MoveToStatesQueueProcessing;
class queueProcessing;

// Обычное состояние
class SimpleStatesQueueProcessing: public ICommandStatesQueueProcessing
{
public:

	SimpleStatesQueueProcessing()
		: queueCommandNew()
	{}

	virtual ~SimpleStatesQueueProcessing() {}

	bool handle(queueProcessing *m) override;

protected:
	QueueCommand					queueCommandNew;		// очередь команд дополнительная
};

// состояние MoveTo
class MoveToStatesQueueProcessing: public ICommandStatesQueueProcessing
{
public:

	bool handle(queueProcessing *m) override;
};

#endif /* _STATES_QUEUE_PROCESSING_H_ */