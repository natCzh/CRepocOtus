#include <string>

#include "service/TourneyService/EventLoop.h"

#include "Command/GameCommand.h"

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
	idsGameObject.push_front(getNextObjectId());
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
		idsGameObject.pop_back();
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
			idsGameObject.pop_back();
		}
		catch (std::exception &e)
		{
			excHendler.Handle(cmd, e)->Execute(); // TODO !! Это надо получать из IOC
		}
	}
	else
		stop();
}

void EventLoop::setICommandToGameObject(size_t index, ICommand_Ptr cmd)
{
	auto cmd_GameObj = collection.getDataForIndex(index);
	if (!std::strcmp(cmd_GameObj->GetType().c_str(), "GameCommand"))
		throw MessageTourneySException("Message failed - id of game's object isn't correct");

	auto cmdGame = dynamic_cast<GameCommand* >(cmd.get());
	cmdGame->addCommand(cmd);
}