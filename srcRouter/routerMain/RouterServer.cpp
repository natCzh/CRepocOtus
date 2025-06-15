#include "routerMain/RouterServer.h"
#include "routerMain/RouterMainClass.h"

using grpc::Status;

RouterServer::RouterServer(RouterAuthorizationClient* authorClient_, RouterSpaceGameServerClient* spaceGameClient_)
    : routerProcess(std::make_shared<RouterMainClass>(authorClient_, spaceGameClient_))
{}

grpc::Status RouterServer::AuthorizationObjR(grpc::ServerContext* context, const AuthObjRRequest* request, AuthObjRReply* response)
{
    size_t typeRegister = (size_t)request->typeregister();
    unsigned long long idObj = routerProcess->AuthorizationObj(typeRegister);
    response->set_idobj(idObj);

    return Status::OK;
}

grpc::Status RouterServer::StartNewGameR(grpc::ServerContext* context, const StartNewGameRRequest* request, StartNewGameRReply* response)
{
    unsigned long long idGame;

    bool result = routerProcess->StartNewGame((unsigned long long)request->idobj(), (std::string)request->idotherobj(), (std::string)request->idotherobj(), idGame);

    response->set_resultcheck(result);
    response->set_idgame(idGame);

    return Status::OK;
}

grpc::Status RouterServer::AddCommandGameR(grpc::ServerContext* context, const AddCommandGameRRequest* request, AddCommandGameRReply* response)
{
    unsigned long long idSender = request->idsender();
    unsigned long long idGame = request->idgame();
    unsigned long long idObj = request->idobj();
    std::string TypeCommand = request->typecommand();
    std::string args = request->args();

    bool result = routerProcess->AddCommandGame(idSender, idGame, idObj, TypeCommand, args);
    // TODO тут надо бы какую-нибудь проверку

    return Status::OK;
}

grpc::Status RouterServer::StopGameR(grpc::ServerContext* context, const StopGameRRequest* request, StopGameRReply* response)
{
    unsigned long long idSender = request->idsender();
    unsigned long long idGame = request->idgame();

    bool result = routerProcess->StopGame(idSender, idGame);
    response->set_resultcheck(result);

    return Status::OK;
}

grpc::Status RouterServer::GetInfGameR(grpc::ServerContext* context, const GetInfGameRRequest* request, GetInfGameRReply* response)
{
    unsigned long long idGame = request->idgame();
    std::string infGame;

    routerProcess->GetInfGame(idGame, infGame);
    response->set_infgame(infGame);

    return Status::OK;
}
