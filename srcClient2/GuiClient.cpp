#include "GuiClient.h"

void GuiClient::connectToServer(const std::string &serverAddress)
{
    m_serverAdderess = serverAddress;
    processingFunction();
}

void GuiClient::processingFunction()
{
    std::cout << "Processing GuiClient starting" << std::endl;

    auto ch = grpc::CreateChannel(m_serverAdderess, grpc::InsecureChannelCredentials());
    if(!ch)
        return;

    grpc::ClientContext ctx;
    stub = client_router::Router::NewStub(ch);
}

// [out] idObj
unsigned long long GuiClient::AuthorizationObj(size_t typeRegister)
{
    client_router::AuthObjRRequest request;
    request.set_typeregister((int)typeRegister);
    client_router::AuthObjRReply response;
    grpc::ClientContext context;

    grpc::Status status = stub->AuthorizationObjR(&context, request, &response);

    if(!status.ok())
    {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return 0;
    }

    return response.idobj();
}

bool GuiClient::StartNewGame(unsigned long long idObj, const std::string &idOtherObj, const std::string &otherArgs, unsigned long long &idGame)
{
    client_router::StartNewGameRRequest request;
    request.set_idobj(idObj);
    request.set_idotherobj(otherArgs);
    request.set_otherargs(otherArgs);
    client_router::StartNewGameRReply response;
    grpc::ClientContext context;

    grpc::Status status = stub->StartNewGameR(&context, request, &response);

    if(!status.ok())
    {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return false;
    }

    idGame = response.idgame();
    return response.resultcheck();
}

bool GuiClient::AddCommandGame(unsigned long long idSender, unsigned long long idGame, unsigned long long idObj, const std::string &TypeCommand, const std::string &args)
{
    client_router::AddCommandGameRRequest request;
    request.set_idsender(idSender);
    request.set_idgame(idGame);
    request.set_idobj(idObj);
    request.set_typecommand(TypeCommand);
    request.set_args(args);
    client_router::AddCommandGameRReply response;
    grpc::ClientContext context;

    grpc::Status status = stub->AddCommandGameR(&context, request, &response);
    if(!status.ok())
    {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return false;
    }

    return true;
}

bool GuiClient::StopGame(unsigned long long idSender, unsigned long long idGame)
{
    client_router::StopGameRRequest request;
    request.set_idsender(idSender);
    request.set_idgame(idGame);
    client_router::StopGameRReply response;
    grpc::ClientContext context;

    grpc::Status status = stub->StopGameR(&context, request, &response);
    if(!status.ok())
    {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return false;
    }

    return response.resultcheck();
}

void GuiClient::GetInfGame(unsigned long long idGame, std::string &infGame)
{
    client_router::GetInfGameRRequest request;
    request.set_idgame(idGame);
    client_router::GetInfGameRReply response;
    grpc::ClientContext context;

    grpc::Status status = stub->GetInfGameR(&context, request, &response);

    if(!status.ok())
    {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return;
    }

    infGame = response.infgame();
}

