﻿#ifndef _I_COMMAND_STATES_QUEUE_PROCESSING_H_
#define _I_COMMAND_STATES_QUEUE_PROCESSING_H_

#include <memory>
#include <string>

#include "ICommand.h"
#include "QueueCommand.h"

/* Интерфейс для все конкретных состояний */
class queueProcessing;

class ICommandStatesQueueProcessing
{
public:

	/// Процесс
	/// @param[out]  true - очередь не пуста, false  - очередь пуста
	virtual bool handle(queueProcessing *) = 0;

	virtual std::string GetType() = 0;

	virtual void pushCommand(ICommand_Ptr commandCur) = 0;
};

using ICommandStatesQueueProcessing_Ptr = std::unique_ptr<ICommandStatesQueueProcessing>;

#endif /* _I_COMMAND_STATES_QUEUE_PROCESSING_H_ */