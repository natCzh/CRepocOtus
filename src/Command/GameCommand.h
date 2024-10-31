#ifndef _GAME_COMMAND_H_
#define _GAME_COMMAND_H_

#include <any>
#include <ctime>
#include <chrono>

#include "Command/ICommand.h"
#include "Common/QueueCommand.h"
#include "IoC/IoCGlobal.h"

class GameCommand: public ICommand
{
public:
	GameCommand(std::shared_ptr<QueueCommand> queue_, const unsigned long long &quant_, size_t scopeIdCur_, ICommand_Ptr init)
		: queue(queue_)
		, quant(quant_)
		, scopeIdCur(scopeIdCur_)
	{
		ioc.Resolve<ICommand_Ptr>("Scopes.Current", &scopeIdCur); // TODO тут должна быть команда переделать !!!!!!!!!!!!

		// TODO команда инициализации ƒќѕ»—ј“№ !!!!
		init->Execute();
	}

	void Execute()
	{
		ioc.Resolve<ICommand_Ptr>("Scopes.Current", &scopeIdCur);

		std::time_t start = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		while (std::difftime(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()), start) <= quant)
		{
			ICommand_Ptr cmd = queue->GetCurrentCommand();
			cmd->Execute();
		}
	}

	void addCommand(ICommand_Ptr commandAdd)
	{
		queue->Push(commandAdd);
	}

	std::string GetType()
	{
		return "GameCommand";
	}

	std::shared_ptr<QueueCommand> getQueuue()
	{
		return queue;
	}
	
private:
	std::shared_ptr<QueueCommand>				queue;
	unsigned long long							quant; // кол-во секунд
	size_t										scopeIdCur;
};

#endif /* _GAME_COMMAND_H_ */
