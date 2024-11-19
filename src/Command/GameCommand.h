#ifndef _GAME_COMMAND_H_
#define _GAME_COMMAND_H_

#include <any>
#include <ctime>
#include <chrono>

#include "Command/ICommand.h"
#include "Common/QueueCommand.h"
#include "IoC/IoC.h"
#include "CommonLib/UObject.h"

extern IoC* ioc;
class GameCommand: public ICommand
{
public:
    GameCommand(std::shared_ptr<QueueCommand> queue_, const unsigned long long &quant_, size_t scopeIdCur_, ICommand_Ptr init)
        : queue(queue_)
        , quant(quant_)
		, scopeIdCur(scopeIdCur_)
	{
        ioc->Resolve<ICommand_Ptr>("Scopes.Current.SetId", &scopeIdCur);

		// TODO команда инициализации ДОПИСАТЬ !!!!
		init->Execute();
	}

	void Execute()
	{
        std::shared_ptr<Scopes::Scope> scopeGames = ioc->Resolve<std::shared_ptr<Scopes::Scope>>("Scopes.Current", &scopeIdCur);

		std::time_t start = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		while (std::difftime(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()), start) <= quant)
		{
			ICommand_Ptr cmd = queue->GetCurrentCommand();
			cmd->Execute();
		}
	}

    /*void addCommand(ICommand_Ptr commandAdd)
	{
		queue->Push(commandAdd);
    }*/

    std::string GetType()
	{
		return "GameCommand";
	}
	
private:
	std::shared_ptr<QueueCommand>				queue;
	unsigned long long							quant; // кол-во секунд
	size_t										scopeIdCur;
};

#endif /* _GAME_COMMAND_H_ */
