#include <QDir>
#include <QCoreApplication>
#include <QPluginLoader>
#include <QDebug>

#include "service/TourneyService/CorePluginBattleCommand.h"
#include "service/TourneyService/IoCGlobal.h"
#include "CommonLib/IPlugin.h"

CorePluginBattleCommand::CorePluginBattleCommand()
{
    ioc = std::make_shared<IoC>();

    // загрузка плагинов
    auto pluginsDir = QDir(QCoreApplication::applicationDirPath());

    #if defined(Q_OS_WIN)
        if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
             pluginsDir.cdUp();
    #endif
    pluginsDir.cd("plugins");

    std::vector<QString> pluginFileNames;
    std::vector<std::string> pluginName;
    const auto entryList = pluginsDir.entryList(QDir::Files);
    for (const QString &fileName : entryList)
    {
        auto xzvz = pluginsDir.absoluteFilePath(fileName);
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        auto sdf = loader.errorString();
        if (plugin)
            pluginFileNames.push_back(fileName);
        auto iShape = qobject_cast<IPlugin *>(plugin);
        auto h1 = iShape->GetType();
        pluginName.push_back(h1);
        qDebug() << QString::fromStdString(h1);
        int sdf1 = 0;

    }
       //for (const QString &fileName : entryList) {

    int dfg = 0;


    // pluginsDir.cd("plugins");
}
