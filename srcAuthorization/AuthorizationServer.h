#pragma once
#include <QObject>
#include <memory>

#include "authorization.grpc.pb.h"

#include "IAuthorizationClass.h"

using namespace authorization;

using grpc::Server;

class AuthorizationServer final : public QObject, public Authorization::Service
{
    Q_OBJECT
public:
    AuthorizationServer();

    ~AuthorizationServer(){}

    grpc::Status CheckAuthorizationObj(grpc::ServerContext* context, const CheckAuthRequest* request, CheckAuthReply* response) override;
    grpc::Status AuthorizationObj(grpc::ServerContext* context, const AuthObjRequest* request, AuthObjReply* response) override;

private:
    std::shared_ptr<IAuthorizationClass>                        authProcess;
};

