#ifndef _QUEUE_COMMAND_H_
#define _QUEUE_COMMAND_H_

#include <memory>
#include <queue>

#include "ICommand.h"

// Класс реализации очереди (хранение)
class QueueCommand
{
public:

	QueueCommand()
		: flagDel(0)
		, maxSize(100)
		, queueCommand()
	{}

	QueueCommand(int maxSize)
		: flagDel(0)
		, maxSize(maxSize)
		, queueCommand()
	{}
	
	virtual ~QueueCommand() {}

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
		auto iter1 = queueCommand.empty();
		queueCommand.push(commandCur);
	}

private:
	int												flagDel;
	unsigned int									maxSize;

	std::queue<ICommand_Ptr>						queueCommand;
};

#endif /* _QUEUE_COMMAND_H_ */