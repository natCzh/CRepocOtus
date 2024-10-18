#ifndef _QUEUE_PROCESSING_H_
#define _QUEUE_PROCESSING_H_

#include <memory>
#include "ICommandStatesQueueProcessing.h"
#include "StatesQueueProcessing.h"
#include "CommandException.h"

///////////////////////////////////////////////////////////////
////////// класс контекста, тот кто работает с очередью
class queueProcessing
{
public:

	queueProcessing()
		: m_handler(ICommandStatesQueueProcessing_Ptr(new SimpleStatesQueueProcessing()))
	{}

	queueProcessing(ICommandStatesQueueProcessing *ICommandPtr)
		: m_handler(ICommandStatesQueueProcessing_Ptr(ICommandPtr))
	{}

	// Устанавливает новое состояние
	void set_currentState(std::unique_ptr<ICommandStatesQueueProcessing> hPtr)
	{
		m_handler = std::move(hPtr);
	}

	/// Выполнение очереди
	void execute()
	{
		bool flagProcess = true;
		while (flagProcess)
		{
			flagProcess = m_handler->handle(this);
			if (!m_handler)
			{
				flagProcess = false;
				throw CommandException("stop queue");
			}
		}
	}

	void pushCommand(ICommand_Ptr commandCur)
	{
		m_handler->pushCommand(commandCur);
	}

	std::string GetTypeStates()
	{
		return m_handler->GetType();
	}

protected:
	std::unique_ptr<ICommandStatesQueueProcessing> m_handler; // ссылка на состояние
};

#endif /* _QUEUE_PROCESSING_H_ */