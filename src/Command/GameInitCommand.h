#ifndef _GANE_INIT_COMMAND_H_
#define _GANE_INIT_COMMAND_H_s

#include <string>
#include <iostream>

#include "ICommand.h"
#include "IoC/IoC.h"
#include "Common/QueueCommand.h"

// Команда инициализации игры
extern IoC* ioc;
class GameInitCommand: public ICommand
{
public:
    GameInitCommand(std::shared_ptr<QueueCommand> queue_, size_t scopeIdCur_)
        : queue(queue_)
        , scopeIdCur(scopeIdCur_)
    {}

    virtual ~GameInitCommand() {}

    void Execute() override
    {
        std::shared_ptr<Scopes::Scope> scopeGames = ioc->Resolve<std::shared_ptr<Scopes::Scope>>("Scopes.Current", &scopeIdCur);

        ioc->Resolve<ICommand_Ptr, std::shared_ptr<QueueCommand> >("IoC.Register", "Game.Queue", queue);
    }

    std::string GetType() override
    {
        return "GameInitCommand";
    }

private:
    std::shared_ptr<QueueCommand>                           queue;
    size_t                                                  scopeIdCur;
};

#endif /* _GANE_INIT_COMMAND_H_ */
