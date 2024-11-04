#ifndef _QUEUE_COMMAND_H
#define _QUEUE_COMMAND_H

#include <queue>
#include <memory>

#include "Command/ICommand.h"

// TODO сделать класс IQueue и от него наследоваться !!!!!!!!!!
class QueueCommand 
{
public:
	QueueCommand(int maxSize)
		: flagDel(0)
		, maxSize(maxSize)
	{}

	std::shared_ptr<ICommand> GetCurrentCommand()
	{
		if (flagDel)
			queueCommand.pop();

		if (!queueCommand.size())
			return nullptr;
		else
		{
			flagDel = 1;
			maxSize--;
			return queueCommand.front();
		}
	}

	void Push(std::shared_ptr<ICommand> commandCur)
	{
		queueCommand.push(commandCur);
	}

private:
	int												flagDel;
	unsigned int									maxSize;

	std::queue<std::shared_ptr<ICommand> >			queueCommand;
};


#endif _QUEUE_COMMAND_H
