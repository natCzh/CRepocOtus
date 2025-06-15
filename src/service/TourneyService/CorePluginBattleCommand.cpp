#include <QDir>
#include <QCoreApplication>
#include <QPluginLoader>
#include <QDebug>
#include <cstring>

#include "service/TourneyService/CorePluginBattleCommand.h"
#include "service/TourneyService/IoCGlobal.h"
#include "CommonLib/IPlugin.h"
#include "Common/SpaceShip.h"

#include "service/Message.h"
#include "CommonLib/IMessagableStartGame.h"
#include "service/TourneyService/MessageAdapterStartGame.h"
#include "inputPlugins/CommandInterpretMoveStopRotateShot/InitCommandInterpretCommand.h"

#include "Command/InitCommonCommand.h"

#include "service/ILogger.h"
#include "service/LoggerSimple.h"

CorePluginBattleCommand::CorePluginBattleCommand()
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
    //LoadPluginForScope(pluginFileNames, scopeIdCur_);
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

        /*int xVel = 1;
        xObj->setProperty("velocity", xVel);
        std::string key1 = "Command.Move";
        ICommand_Ptr f = ioc->Resolve<ICommand_Ptr>(key1, xObj);
        auto strd = f->GetType();
        f->Execute();
        int werwe = 0;*/

        /*if (strcmp(h1.c_str(), "RotateCommandPlugin") == 0)
        {
            int xVel = 1;
                    xObj->setProperty("directionAngular", xVel);
                    std::string key1 = "Command.Rotate";
                    ICommand_Ptr f = ioc->Resolve<ICommand_Ptr>(key1, xObj);
                    auto strd = f->GetType();
                    f->Execute();

        }*/
        /*if (strcmp(h1.c_str(), "ShotCommandPlugin") == 0)
        {
            int xVel = 1;
                    xObj->setProperty("numberShot", xVel);
                    std::string key1 = "Command.Shot";
                    ICommand_Ptr f = ioc->Resolve<ICommand_Ptr>(key1, xObj);
                    auto strd = f->GetType();
                    f->Execute();
        }*/
    }
}

void CorePluginBattleCommand::LoadPluginForScope(const std::vector<std::string> &listNamePlugin, size_t scopeIdCur_)
{
    qDebug() << "Plugin load for scope " << scopeIdCur_;
    ioc->Resolve<void>("Scopes.Current.SetId", scopeIdCur_);
    CorePluginBattleCommand::LoadPlugin(listNamePlugin);
    InitCommandInterpretCommand cmd; cmd.Execute(); // TODO вынести в плагин
}

size_t CorePluginBattleCommand::getNewGame(UObject_Ptr message)
{
    // сначало работа со скоупами !!!!!!!!!!
    scopeIdForIoc.push_back(storageScope.getNewScope());
    ioc->Resolve<void>("Scopes.Current.SetId", scopeIdForIoc.back());

    std::shared_ptr<IMessagableStartGame> messagable = std::make_shared<MessageAdapterStartGame>(message);

    /// [in] idObjs - ид объектов, idObjsType - ид типов для этих объектов(все это с маршрутизатора приходит)
    idGameAndThread newIdGame = tourneyService.CreateNewGame(scopeIdForIoc.back(), messagable->getIdObjects(), messagable->getTypeObjs());

    // TODO тут надо переделать и загружать для каждого свое
    storageScope.saveScopeWithIdGame(scopeIdForIoc.back(), newIdGame);
    std::unordered_map<unsigned long long, std::vector<std::string> > vectExistParam = ioc->Resolve<std::unordered_map<unsigned long long, std::vector<std::string> > >("GameItems.listPlugins");
    std::vector<std::string> loadPlugin = vectExistParam[messagable->getIdObjects()[0]];
    LoadPluginForScope(loadPlugin, scopeIdForIoc.back());

    return newIdGame.idGame;
}

void CorePluginBattleCommand::addCommandForGame(std::shared_ptr<Message> message)
{
    std::shared_ptr<IMessagable> messagable = std::make_shared<MessageAdapter>(message);
    std::pair<size_t,size_t > pairIdScopeIdThr = storageScope.getIdInfScope(messagable->getIdGame());

    idGameAndThread idGame{messagable->getIdGame(), pairIdScopeIdThr.second};
    tourneyService.AddCommandToGame(idGame, pairIdScopeIdThr.first, message);
}

void CorePluginBattleCommand::startNewGame(size_t idGame, size_t idThread)
{
    idGameAndThread idGameStr{idGame, idThread};
    tourneyService.StartNewGame(idGameStr);
}

void CorePluginBattleCommand::stopGame(size_t idGame, size_t idThread)
{
    idGameAndThread idGameStr{idGame, idThread};
    tourneyService.StopGame(idGameStr);
}

std::string CorePluginBattleCommand::getLogGame(size_t idGame)
{
    std::pair<size_t,size_t > infScope = storageScope.getIdInfScope(idGame);
    ioc->Resolve<void>("Scopes.Current.SetId", infScope.first);

    LoggerSimple log;
    return log.logProcess();
}



