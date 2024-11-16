#ifndef _CORE_PLUGIN_BATTLE_COMMAND_H_
#define _CORE_PLUGIN_BATTLE_COMMAND_H_

#include <QString>
#include <QStringList>
#include <QObject>

#include <memory>
#include <vector>

#include "../../CommonLib/UObject.h"
class CorePluginBattleCommand
{
public:
	CorePluginBattleCommand();

    virtual ~CorePluginBattleCommand(){}

    std::vector<std::string> GetPossiblePlugin();
    void LoadPluginForScope(const std::vector<std::string> &listNamePlugin, size_t scopeIdCur_);

protected:
    void initPossiblePlugin();
    bool checkNamePlugin(const std::string &namePluginCur);
    void LoadPlugin(const std::vector<std::string> &listNamePlugin);

private:
    std::vector<std::string>                 pluginFileNames;
    std::vector<QObject*>                    pluginInstance;
    UObject_Ptr                              xObj;
};

#endif /* _CORE_PLUGIN_BATTLE_COMMAND_H_ */
