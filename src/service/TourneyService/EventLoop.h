#ifndef _EVENT_LOOP_H_
#define _EVENT_LOOP_H_

#include <thread>
#include <functional>

#include "src/Common/ThreadDeque.h"
#include "src/Command/ICommand.h"
#include "src/Common/CommandException.h"
#include "src/service/ExceptionHendler.h"
#include "src/Exception/MessageTourneySException.h"

class EventLoop
{
public:

	EventLoop()
		: flagStop(false)
		, waitMilliSec(1)
		, threadCur(nullptr)
		, gameObjectId(0)
	{
		behavior = std::bind(&EventLoop::behaviorCommon, this);
	}

	EventLoop(ExceptionHendler &excHendler_, int waitMilliSec_ = 10)
		: flagStop(false)
		, waitMilliSec(waitMilliSec_)
		, excHendler(excHendler_)
		, gameObjectId(0)
	{
		//this->threadCur = std::thread{ &CommandCollection::loop, this };
	}

	~EventLoop()
	{
		stop();
	}

	void setExceptionHandler(ExceptionHendler &excHendler_);

	void stop();

	void add(ICommand_Ptr cmd);

	void startLoop();

	void loop();

	void behaviorCommon();

	void softStop();

	void behaviorSS();

	unsigned long long getNextObjectId()
	{
		return gameObjectId++;
	}

	// нахождение индекса в очереди игр
	size_t findIndexCollectionGameId(unsigned long long gameId)
	{
		auto indexGameId = std::find(idsGameObject.begin(), idsGameObject.end(), gameId);
		if (indexGameId == idsGameObject.end())
			throw MessageTourneySException("id game object isn't correct");
		return std::distance(idsGameObject.begin(), indexGameId);
	}

	void setICommandToGameObject(size_t index, ICommand_Ptr cmd);

protected:
	ThreadDeque<ICommand_Ptr>				collection;
	bool									flagStop;				// флаг остановки, false - работаем
	int										waitMilliSec;			// кол-во миллисекунд, которые ждем команду
	ExceptionHendler						excHendler;
	std::thread								*threadCur;
	std::function<void()>					behavior;
	std::deque<long long>					idsGameObject;			// ид всех объектов данной игры - идут на пару с collection, -1 - если это не игра
	long long								gameObjectId;
};

#endif /* _EVENT_LOOP_H_ */