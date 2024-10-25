#ifndef _COMMAND_COLLECTION_H_
#define _COMMAND_COLLECTION_H_

#include <thread>
#include <functional>

#include "src/Common/ThreadDeque.h"
#include "src/Command/ICommand.h"
#include "src/Common/CommandException.h"
#include "src/service/ExceptionHendler.h"

class CommandCollection
{
public:

	//using Behavior = void(*)();

	CommandCollection()
		: flagStop(false)
		, waitMilliSec(1)
	{
		this->threadCur = std::thread{ &CommandCollection::loop, this };
		behavior = std::bind(&CommandCollection::behaviorSS, this);
	}

	CommandCollection(ExceptionHendler &excHendler_, int waitMilliSec_ = 10)
		: flagStop(false)
		, waitMilliSec(waitMilliSec_)
		, excHendler(excHendler_)
	{
		this->threadCur = std::thread{ &CommandCollection::loop, this };
	}

	~CommandCollection() {}

	void setExceptionHandler(ExceptionHendler &excHendler_)
	{
		excHendler = excHendler_;
	}

	void stop()
	{
		flagStop = true;
	}

	void add(ICommand_Ptr cmd)
	{
		collection.push(cmd);
	}

	void startLoop()
	{
		// before start hook
		threadCur.detach();
		// after stop hook
	}

	void loop()
	{
		while (!flagStop)
			behavior();
	}

	void behaviorCommon()
	{
		auto cmd = collection.pop(waitMilliSec);
		try
		{
			cmd->Execute();
		}
		catch (std::exception &e)
		{
			excHendler.Handle(cmd, e)->Execute(); // TODO !! Это надо получать из IOC
		}
	}

	void behaviorSS()
	{
		if (collection.getSize() > 0)
		{
			auto cmd = collection.pop(waitMilliSec);
			try
			{
				cmd->Execute();
			}
			catch (std::exception &e)
			{
				excHendler.Handle(cmd, e)->Execute(); // TODO !! Это надо получать из IOC
			}
		}
		else
			stop();
	}

protected:
	ThreadDeque<ICommand_Ptr>				collection;
	bool									flagStop;				// флаг остановки, false - работаем
	int										waitMilliSec;			// кол-во миллисекунд, которые ждем команду
	ExceptionHendler						excHendler;
	std::thread								threadCur;
	std::function<void()>					behavior;
};

#endif /* _COMMAND_COLLECTION_H_ */