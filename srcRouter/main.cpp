#include <QCoreApplication>
#include <QDebug>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "RouterAuthorizationClient.h"
#include "RouterSpaceGameServerClient.h"

#include <thread>
#include <chrono>

using grpc::ServerBuilder;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /////////////// connect Authorization server
    RouterAuthorizationClient asrv;

    std::string server_address("127.0.0.1:35451");
    grpc::EnableDefaultHealthCheckService(true);

    asrv.connectToServer(server_address);

    //////////// проверка для Authorization server
    /*unsigned long long idObj = 0;
    unsigned long long typeObj;
    bool flagAuth = asrv.CheckAuthorizationObj(idObj, typeObj);

    unsigned long long typeRegister = 1;
    unsigned long long idObj2 = asrv.AuthorizationObj(typeRegister);
    bool flagAuth2 = asrv.CheckAuthorizationObj(idObj2, typeObj);

    unsigned long long idObj3 = asrv.AuthorizationObj(typeRegister);
    bool flagAuth3 = asrv.CheckAuthorizationObj(idObj3, typeObj);*/

    /////////////// connect SpaceGame server
    RouterSpaceGameServerClient servSpaceGame;

    std::string server_address_spaceGame("127.0.0.1:35452");
    grpc::EnableDefaultHealthCheckService(true);
    servSpaceGame.connectToServer(server_address_spaceGame);
    //////////// проверка для SpaceGame server
    unsigned long long idObj = 0;
    int typeRegister = 1;
    std::string idOtherObj = "";
    std::string otherArgs = "";
    unsigned long long idGame = servSpaceGame.StartNewGame(idObj, typeRegister, idOtherObj, otherArgs);

    std::string TypeCommand = "CommandInterpret.StartMove";
    std::string args = "velocity, 1";
    servSpaceGame.AddCommandGame(idObj, idGame, idObj, TypeCommand, args);


    std::string TypeCommandShot = "CommandInterpret.Shot";
    std::string argsShot = "";
    servSpaceGame.AddCommandGame(idObj, idGame, idObj, TypeCommandShot, argsShot);
    servSpaceGame.AddCommandGame(idObj, idGame, idObj, TypeCommandShot, argsShot);
    servSpaceGame.AddCommandGame(idObj, idGame, idObj, TypeCommandShot, argsShot);


    std::string TypeCommandRotate = "CommandInterpret.Rotate";
    std::string argsRotate = "directionAngular, 1";
    servSpaceGame.AddCommandGame(idObj, idGame, idObj, TypeCommandRotate, argsRotate);

    servSpaceGame.AddCommandGame(idObj, idGame, idObj, TypeCommandShot, argsShot);
    servSpaceGame.AddCommandGame(idObj, idGame, idObj, TypeCommandShot, argsShot);
    servSpaceGame.AddCommandGame(idObj, idGame, idObj, TypeCommandShot, argsShot);

    std::string argsRotate_ = "directionAngular, -1";
    servSpaceGame.AddCommandGame(idObj, idGame, idObj, TypeCommandRotate, argsRotate_);

    std::string TypeCommandStopMove = "CommandInterpret.StopMove";
    std::string argsStopMove = "";
    servSpaceGame.AddCommandGame(idObj, idGame, idObj, TypeCommandStopMove, argsStopMove);

    servSpaceGame.AddCommandGame(idObj, idGame, idObj, TypeCommandShot, argsShot);
    servSpaceGame.AddCommandGame(idObj, idGame, idObj, TypeCommandShot, argsShot);
    servSpaceGame.AddCommandGame(idObj, idGame, idObj, TypeCommandShot, argsShot);

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(10s);


    bool flagResult = servSpaceGame.StopGame(idGame);
    if (!flagResult)
        qDebug() << "ERROR stop GAME";

    servSpaceGame.AddCommandGame(idObj, idGame, idObj, TypeCommandShot, argsShot);


    return a.exec();
}
