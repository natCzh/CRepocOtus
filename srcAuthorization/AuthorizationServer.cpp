#include "AuthorizationServer.h"
#include "AuthorizationClass.h"

using grpc::Status;

AuthorizationServer::AuthorizationServer()
    : authProcess(std::make_shared<AuthorizationClass>())
{}

grpc::Status AuthorizationServer::AuthorizationObj(grpc::ServerContext* context, const AuthObjRequest* request, AuthObjReply* response)
{
    unsigned long long idObjCur = authProcess->authorizationObj(request->typeregister());
    response->set_idobj(idObjCur);
    return Status::OK;
}

grpc::Status AuthorizationServer::CheckAuthorizationObj(grpc::ServerContext* context, const CheckAuthRequest* request, CheckAuthReply* response)
{
    unsigned long long typeObj;
    bool flagCheck = authProcess->checkAuthorizationObj(request->idobj(), typeObj);
    response->set_resultcheck(flagCheck);
    response->set_typeobj(typeObj);

    return Status::OK;
}
