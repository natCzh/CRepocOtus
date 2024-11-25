#include <QCoreApplication>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "RouterSpaceGameClient.h"

using grpc::ServerBuilder;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RouterSpaceGameClient asrv;

    std::string server_address("127.0.0.1:35451");
    grpc::EnableDefaultHealthCheckService(true);

    asrv.connectToServer(server_address);

    unsigned long long idObj = 0;
    unsigned long long typeObj;
    bool flagAuth = asrv.CheckAuthorizationObj(idObj, typeObj);

    unsigned long long typeRegister = 1;
    unsigned long long idObj2 = asrv.AuthorizationObj(typeRegister);
    bool flagAuth2 = asrv.CheckAuthorizationObj(idObj2, typeObj);

    unsigned long long idObj3 = asrv.AuthorizationObj(typeRegister);
    bool flagAuth3 = asrv.CheckAuthorizationObj(idObj3, typeObj);




    return a.exec();
}
