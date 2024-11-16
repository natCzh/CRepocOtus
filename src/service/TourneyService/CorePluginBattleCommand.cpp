#include <QDir>
#include <QCoreApplication>
#include <QPluginLoader>
#include <QDebug>

#include "service/TourneyService/CorePluginBattleCommand.h"
#include "service/TourneyService/IoCGlobal.h"
#include "CommonLib/IPlugin.h"
#include "Common/SpaceShip.h"

CorePluginBattleCommand::CorePluginBattleCommand()
    : xObj(std::make_shared<SpaceShip>())
{
    ioc = new IoC();

    initPossiblePlugin();
}

void CorePluginBattleCommand::initPossiblePlugin()
{
    // загрузка плагинов
    auto pluginsDir = QDir(QCoreApplication::applicationDirPath());
    #if defined(Q_OS_WIN)
        if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
             pluginsDir.cdUp();
    #endif
    pluginsDir.cd("plugins");

    QStringList pluginFileNamesCur = pluginsDir.entryList(QDir::Files);
    for (const QString &fileName : pluginFileNamesCur)
    {
        auto xzvz = pluginsDir.absoluteFilePath(fileName);
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        // auto sdf = loader.errorString();
        if (plugin)
        {
            pluginFileNames.push_back(fileName.toStdString());
            pluginInstance.push_back(plugin);
        }
    }

    size_t scopeIdCur_ = 0;
    LoadPluginForScope(pluginFileNames, scopeIdCur_);
}

std::vector<std::string> CorePluginBattleCommand::GetPossiblePlugin()
{
    return pluginFileNames;
}

bool CorePluginBattleCommand::checkNamePlugin(const std::string &namePluginCur)
{
    auto iter = std::find(pluginFileNames.begin(), pluginFileNames.end(), namePluginCur);
    if (iter != pluginFileNames.end())
        return true;
    return false;
}

void CorePluginBattleCommand::LoadPlugin(const std::vector<std::string> &listNamePlugin)
{
    for (const std::string &fileName : listNamePlugin)
    {
        if (!checkNamePlugin(fileName))
            continue;

        auto iter = std::find(pluginFileNames.begin(), pluginFileNames.end(), fileName);
        auto indexPlugin = std::distance(pluginFileNames.begin(), iter);
        auto iPlugin = qobject_cast<IPlugin *>(pluginInstance[indexPlugin]);
        auto h1 = iPlugin->GetType();
        qDebug() << "Plugin load " << QString::fromStdString(h1);
        iPlugin->InitPlugin(ioc);
        iPlugin->Load();
#include "CommonLib/UObject.h"

        int xVel = 1;
        xObj->setProperty("velocity", xVel);
        std::string key1 = "Command.Move";
        ICommand_Ptr f = ioc->Resolve<ICommand_Ptr>(key1, xObj);
        auto strd = f->GetType();
        f->Execute();
        int werwe = 0;
    }
}

void CorePluginBattleCommand::LoadPluginForScope(const std::vector<std::string> &listNamePlugin, size_t scopeIdCur_)
{
    qDebug() << "Plugin load for scope " << scopeIdCur_;
    ioc->Resolve<void>("Scopes.Current.SetId", scopeIdCur_);
    CorePluginBattleCommand::LoadPlugin(listNamePlugin);
}

