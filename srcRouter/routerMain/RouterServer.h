#ifndef _ROUTER_SERVER_H_
#define _ROUTER_SERVER_H_

#include <QObject>
#include <memory>

#include "routerMain/client_router.grpc.pb.h"

#include "routerMain/IRouterMainClass.h"

#include "authorization/RouterAuthorizationClient.h"
#include "serverGame/RouterSpaceGameServerClient.h"

using namespace client_router;

using grpc::Server;

// главная класс роутера как соединение со всеми сервисами
class RouterServer final : public QObject, public Router::Service
{
public:

    RouterServer(RouterAuthorizationClient *authorClient_, RouterSpaceGameServerClient* spaceGameClient_);

    virtual ~RouterServer(){}

    grpc::Status AuthorizationObjR(grpc::ServerContext* context, const AuthObjRRequest* request, AuthObjRReply* response) override;
    grpc::Status StartNewGameR(grpc::ServerContext* context, const StartNewGameRRequest* request, StartNewGameRReply* response) override;
    grpc::Status AddCommandGameR(grpc::ServerContext* context, const AddCommandGameRRequest* request, AddCommandGameRReply* response) override;
    grpc::Status StopGameR(grpc::ServerContext* context, const StopGameRRequest* request, StopGameRReply* response) override;
    grpc::Status GetInfGameR(grpc::ServerContext* context, const GetInfGameRRequest* request, GetInfGameRReply* response) override;
\
private:
    std::shared_ptr<IRouterMainClass>                       routerProcess;
};

#endif /* _ROUTER_SERVER_H_ */
