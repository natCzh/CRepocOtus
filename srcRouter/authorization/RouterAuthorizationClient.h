#ifndef _ROUTER_AUTHORIZATION_CLIENT_H_
#define _ROUTER_AUTHORIZATION_CLIENT_H_

#include <string>
#include <memory>

#include <grpc/grpc.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

#include "authorization/authorization.grpc.pb.h"

using grpc::ClientAsyncReaderWriter;
using grpc::Channel;

class RouterAuthorizationClient
{
public:

    RouterAuthorizationClient(){}

    virtual ~RouterAuthorizationClient(){}

    void connectToServer(const std::string &serverAddress);

    /// [out] зарегестрирован пользователь или нет
    bool CheckAuthorizationObj(unsigned long long idObj, unsigned long long &typeObj);

    unsigned long long AuthorizationObj(unsigned long long typeRegister);

protected:
     void processingFunction();
\
private:

    std::string                                                      m_serverAdderess;
    std::unique_ptr<authorization::Authorization::Stub>              stub;
};

#endif /* _ROUTER_AUTHORIZATION_CLIENT_H_ */
