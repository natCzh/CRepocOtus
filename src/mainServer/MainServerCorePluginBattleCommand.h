#ifndef _MAIN_SERVER_CORE_PLUGIN_BATTLE_COMMAND_H_
#define _MAIN_SERVER_CORE_PLUGIN_BATTLE_COMMAND_H_

#include <QObject>
#include <memory>
#include "boost/any.hpp"

#include "mainServer/router_serverGame.grpc.pb.h"

#include "service/TourneyService/ICorePluginBattleCommand.h"

using namespace router_serverGame;

using grpc::Server;

class MainServerCorePluginBattleCommand final : public QObject, public ServerGame::Service
{
    Q_OBJECT
public:

    MainServerCorePluginBattleCommand();

    ~MainServerCorePluginBattleCommand(){}

    grpc::Status StartNewGame(grpc::ServerContext* context, const StartNewGameRequest* request, StartNewGameReply* response) override;
    grpc::Status AddCommandGame(grpc::ServerContext* context, const AddCommandGameRequest* request, AddCommandGameReply* response) override;
    grpc::Status StopGame(grpc::ServerContext* context, const StopGameRequest* request, StopGameReply* response) override;

protected:
    // читает только один параметр
    void getMapFromStr(std::string str, std::map<std::string, boost::any> &mapCur);

private:
    std::shared_ptr<ICorePluginBattleCommand>                        core;
};

#endif /* _MAIN_SERVER_CORE_PLUGIN_BATTLE_COMMAND_H_ */
