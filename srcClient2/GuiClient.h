#ifndef _GUI_CLIENT_H_
#define _GUI_CLIENT_H_

#include <string>
#include <memory>

#include <grpc/grpc.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

#include "protoFile/client_router.grpc.pb.h"

using grpc::ClientAsyncReaderWriter;
using grpc::Channel;

class GuiClient
{

public:

    GuiClient(){}
    virtual ~GuiClient(){}

    void connectToServer(const std::string &serverAddress);

    // [out] idObj
    unsigned long long AuthorizationObj(size_t typeRegister);

    // [out] result bool
    // [in - out] typeObj
    bool StartNewGame(unsigned long long idObj, const std::string &idOtherObj, const std::string &otherArgs, unsigned long long &typeObj);

    bool AddCommandGame(unsigned long long idSender, unsigned long long idGame, unsigned long long idObj, const std::string &TypeCommand, const std::string &args);

    bool StopGame(unsigned long long idSender, unsigned long long idGame);

    // [in-out] infGame - информация об игре
    void GetInfGame(unsigned long long idGame, std::string &infGame);

protected:
    void processingFunction();

private:

    std::string                                                      m_serverAdderess;
    std::unique_ptr<client_router::Router::Stub>                     stub;
};

#endif /* _GUI_CLIENT_H_ */
