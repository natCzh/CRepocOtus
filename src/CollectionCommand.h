#ifndef _COLLECTION_COMMAND_H_
#define _COLLECTION_COMMAND_H_

#include <thread>
#include <functional>

#include "src/Common/ThreadDeque.h"
#include "src/Command/ICommand.h"
#include "src/Common/CommandException.h"
#include "src/service/ExceptionHendler.h"

class CommandCollection
{
public:

	CommandCollection()
		: flagStop(false)
		, waitMilliSec(1)
		, threadCur(nullptr)
	{
		behavior = std::bind(&CommandCollection::behaviorCommon, this);
	}

	CommandCollection(ExceptionHendler &excHendler_, int waitMilliSec_ = 10)
		: flagStop(false)
		, waitMilliSec(waitMilliSec_)
		, excHendler(excHendler_)
	{
		//this->threadCur = std::thread{ &CommandCollection::loop, this };
	}

	~CommandCollection()
	{
		stop();
	}

	void setExceptionHandler(ExceptionHendler &excHendler_)
	{
		excHendler = excHendler_;
	}

	void stop()
	{
		if(this->threadCur != nullptr)
        {
            flagStop = true;
            // this->threadCur->join();
            delete this->threadCur;
            this->threadCur = nullptr;
        }
	}

	void add(ICommand_Ptr cmd)
	{
		collection.push(cmd);
	}

	void startLoop()
	{
		// before start hook
		threadCur = new std::thread{ &CommandCollection::loop, this };
		threadCur->detach();
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

	void softStop()
	{
		behavior = std::bind(&CommandCollection::behaviorSS, this);
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
	std::thread								*threadCur;
	std::function<void()>					behavior;
};

#endif /* _COLLECTION_COMMAND_H_ */