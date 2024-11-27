#ifndef _I_CORE_PLUGIN_BATTLE_COMMAND_H_
#define _I_CORE_PLUGIN_BATTLE_COMMAND_H_

#include <vector>
#include <string>

#include "../../CommonLib/UObject.h"
#include "service/Message.h"

class ICorePluginBattleCommand
{
public:
    virtual ~ICorePluginBattleCommand(){}

    virtual std::vector<std::string> GetPossiblePlugin() = 0;

    /// должны вернуть ид игры
    virtual size_t getNewGame(UObject_Ptr message) = 0;

    /// отправляем команду в игру
    virtual void addCommandForGame(std::shared_ptr<Message> message) = 0;

    virtual void startNewGame(size_t idGame, size_t idThread) = 0;
    virtual void stopGame(size_t idGame, size_t idThread) = 0;
};

#endif /* _I_CORE_PLUGIN_BATTLE_COMMAND_H_ */
