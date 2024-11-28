#include <iostream>

#include "RouterSpaceGameServerClient.h"

void RouterSpaceGameServerClient::connectToServer(const std::string &serverAddress)
{
    m_serverAdderess = serverAddress;
    processingFunction();
}

void RouterSpaceGameServerClient::processingFunction()
{
    std::cout << "Processing RouterSpaceGameClass starting" << std::endl;

    auto ch = grpc::CreateChannel(m_serverAdderess, grpc::InsecureChannelCredentials());
    if(!ch)
        return;

    grpc::ClientContext ctx;
    stub = router_serverGame::ServerGame::NewStub(ch);
}

unsigned long long RouterSpaceGameServerClient::StartNewGame(unsigned long long idObj, int typeRegister, std::string idOtherObj, std::string otherArgs)
{
    router_serverGame::StartNewGameRequest request;
    request.set_idobj(idObj);
    request.set_typeregister(typeRegister);
    request.set_idotherobj(idOtherObj);
    request.set_otherargs(otherArgs);

    router_serverGame::StartNewGameReply response;
    grpc::ClientContext context;
    grpc::Status status = stub->StartNewGame(&context, request, &response);
    if(!status.ok())
    {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return 0;
    }

    return response.idgame();
}

void RouterSpaceGameServerClient::AddCommandGame(unsigned long long idSender, unsigned long long idGame,
                                                 unsigned long long idObj, const std::string &TypeCommand, const std::string &args)
{
    router_serverGame::AddCommandGameRequest request;
    request.set_idsender(idSender);
    request.set_idgame(idGame);
    request.set_idobj(idObj);
    request.set_typecommand(TypeCommand);
    request.set_args(args);

    router_serverGame::AddCommandGameReply response;
    grpc::ClientContext context;

    grpc::Status status = stub->AddCommandGame(&context, request, &response);
    if(!status.ok())
    {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
}

bool RouterSpaceGameServerClient::StopGame(unsigned long long idGame)
{
    router_serverGame::StopGameRequest request;
    request.set_idgame(idGame);

    router_serverGame::StopGameReply response;
    grpc::ClientContext context;

    grpc::Status status = stub->StopGame(&context, request, &response);
    if(!status.ok())
    {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return false;
    }

    return response.resultcheck();
}



