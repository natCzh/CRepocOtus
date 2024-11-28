#include <iostream>

#include "RouterAuthorizationClient.h"

void RouterAuthorizationClient::connectToServer(const std::string &serverAddress)
{
    m_serverAdderess = serverAddress;
    processingFunction();
}

void RouterAuthorizationClient::processingFunction()
{
    std::cout << "Processing RouterSpaceGameClass starting" << std::endl;

    auto ch = grpc::CreateChannel(m_serverAdderess, grpc::InsecureChannelCredentials());
    if(!ch)
        return;

    grpc::ClientContext ctx;
    stub = authorization::Authorization::NewStub(ch);
}

bool RouterAuthorizationClient::CheckAuthorizationObj(unsigned long long idObj, unsigned long long &typeObj)
{
    authorization::CheckAuthRequest request;
    request.set_idobj(idObj);
    authorization::CheckAuthReply response;
    grpc::ClientContext context;

    grpc::Status status = stub->CheckAuthorizationObj(&context, request, &response);
    if(!status.ok())
    {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return false;
    }

    typeObj = response.typeobj();
    return response.resultcheck();
}

unsigned long long RouterAuthorizationClient::AuthorizationObj(unsigned long long typeRegister)
{
    authorization::AuthObjRequest request;
    request.set_typeregister(typeRegister);
    authorization::AuthObjReply response;
    grpc::ClientContext context;

    grpc::Status status = stub->AuthorizationObj(&context, request, &response);

    if(!status.ok())
    {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return 0;
    }

    return response.idobj();
}
