#ifndef _CORE_PLUGIN_BATTLE_COMMAND_H_
#define _CORE_PLUGIN_BATTLE_COMMAND_H_

#include <QString>
#include <QStringList>
#include <QObject>

#include <memory>
#include <vector>

#include "../../CommonLib/UObject.h"
#include "service/StorageIdScope.h"
#include "service/TourneyService/TourneyService.h"



class CorePluginBattleCommand
{
public:
	CorePluginBattleCommand();

    virtual ~CorePluginBattleCommand(){}

    std::vector<std::string> GetPossiblePlugin();

    /// должны вернуть ид игры
    size_t getNewGame(UObject_Ptr message);


protected:
    void initPossiblePlugin();
    bool checkNamePlugin(const std::string &namePluginCur);
    void LoadPlugin(const std::vector<std::string> &listNamePlugin);
    void LoadPluginForScope(const std::vector<std::string> &listNamePlugin, size_t scopeIdCur_);

private:
    std::vector<std::string>                 pluginFileNames;
    std::vector<QObject*>                    pluginInstance;
    StorageIdScope                           storageScope;
    TourneyService                           tourneyService;
};

#endif /* _CORE_PLUGIN_BATTLE_COMMAND_H_ */
