#include <QCoreApplication>

#include "mainServer/MainServerCorePluginBattleCommand.h"

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

using grpc::ServerBuilder;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MainServerCorePluginBattleCommand asrv;

    std::string server_address("127.0.0.1:35452");
    grpc::EnableDefaultHealthCheckService(true);
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&asrv);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    server->Wait();

    return a.exec();
}
