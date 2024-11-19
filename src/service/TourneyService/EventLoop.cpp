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
	collection.push(cmd);
}

size_t EventLoop::addNewGame(ICommand_Ptr cmdInit, size_t scopeIdCur)
{
    size_t idCurGame = getNextGameId();
    queueGame[idCurGame] = std::make_shared<QueueCommand>(maxSizeQueueGame);

    // это повторяющаяся команда в коллекции очереди самих игр
    ICommand_Ptr cmd = std::make_shared<GameCommandPlayRepeat>(collection, std::make_shared<GameCommand>(queueGame[idCurGame], quantGame, scopeIdCur, cmdInit));
    collection.push(cmd);

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
	auto cmd = collection.pop(waitMilliSec);
	try
	{
		cmd->Execute();
        idsScopesGame.pop_back();
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
	if (collection.getSize() > 0)
	{
		auto cmd = collection.pop(waitMilliSec);
		try
		{
			cmd->Execute();
            idsScopesGame.pop_back();
		}
		catch (std::exception &e)
		{
			excHendler.Handle(cmd, e)->Execute(); // TODO !! Это надо получать из IOC
		}
	}
	else
		stop();
}

void EventLoop::addCommandToGameForObject(size_t index, ICommand_Ptr cmd)
{
    auto cmd_Game = collection.getDataForIndex(index);
    if (!std::strcmp(cmd_Game->GetType().c_str(), "GameCommand"))
        throw MessageTourneySException("Message failed - id of game's isn't correct");

	auto cmdGame = dynamic_cast<GameCommand* >(cmd.get());
	cmdGame->addCommand(cmd);
}
