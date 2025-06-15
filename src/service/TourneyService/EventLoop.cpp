#include <cstring>

#include "service/TourneyService/EventLoop.h"

#include "Command/GameCommand.h"
#include "Command/GameCommandPlayRepeat.h"

std::atomic<size_t> EventLoop::gameId(0);

void EventLoop::setExceptionHandler(ExceptionHendler &excHendler_)
{
	excHendler = excHendler_;
}

void EventLoop::stop()
{
	if(this->threadCur != nullptr)
    {
        flagStop = true;
        // this->threadCur->join();
        delete this->threadCur;
        this->threadCur = nullptr;
    }
}

void EventLoop::add(ICommand_Ptr cmd)
{
    collection->push(cmd);
}

size_t EventLoop::addNewGame(ICommand_Ptr cmdInit, size_t scopeIdCur)
{
    size_t idCurGame = getNextGameId();
    queueGame[idCurGame] = std::make_shared<QueueCommand>(maxSizeQueueGame);

    ICommand_Ptr cmdGameCommand = std::make_shared<GameCommand>(queueGame[idCurGame], quantGame, scopeIdCur, cmdInit);

    //std::shared_ptr<QueueCommand> queue_, const unsigned long long &quant_, size_t scopeIdCur_, ICommand_Ptr init
    // это повторяющаяся команда в коллекции очереди самих игр
    ICommand_Ptr cmd = std::make_shared<GameCommandPlayRepeat>(collection, cmdGameCommand);
    collection->push(cmd);

    return idCurGame;
}

void EventLoop::startLoop()
{
	// before start hook
	threadCur = new std::thread{ &EventLoop::loop, this };
	threadCur->detach();
	// after stop hook
}

void EventLoop::loop()
{
	while (!flagStop)
		behavior();
}

void EventLoop::behaviorCommon()
{
    auto cmd = collection->pop(waitMilliSec);
	try
	{
		cmd->Execute();
	}
	catch (std::exception &e)
	{
		excHendler.Handle(cmd, e)->Execute(); // TODO !! Это надо получать из IOC
	}
}

void EventLoop::softStop()
{
	behavior = std::bind(&EventLoop::behaviorSS, this);
}

void EventLoop::behaviorSS()
{
    if (collection->getSize() > 0)
	{
        auto cmd = collection->pop(waitMilliSec);
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
