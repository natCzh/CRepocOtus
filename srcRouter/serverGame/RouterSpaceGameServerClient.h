#ifndef _ROUTER_SPACE_GAME_SERVER_CLIENT_H_
#define _ROUTER_SPACE_GAME_SERVER_CLIENT_H_

#include <string>
#include <memory>

#include <grpc/grpc.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

#include "serverGame/router_serverGame.grpc.pb.h"

using grpc::ClientAsyncReaderWriter;
using grpc::Channel;

// соединение с сервисом игры
class RouterSpaceGameServerClient
{
public:

    RouterSpaceGameServerClient(){}

    virtual ~RouterSpaceGameServerClient(){}

    void connectToServer(const std::string &serverAddress);

    unsigned long long StartNewGame(unsigned long long idObj, int typeRegister, std::string idOtherObj, std::string otherArgs);
    void AddCommandGame(unsigned long long idSender, unsigned long long idGame,unsigned long long idObg,
                        const std::string &TypeCommand, const std::string &args);
    bool StopGame(unsigned long long idGame);

    std::string GetLogGame(size_t idGame);

    /// [out] зарегестрирован пользователь или нет
   //bool CheckAuthorizationObj(unsigned long long idObj, unsigned long long &typeObj);

    // unsigned long long AuthorizationObj(unsigned long long typeRegister);

protected:
     void processingFunction();
\
private:

    std::string                                                      m_serverAdderess;
    std::unique_ptr<router_serverGame::ServerGame::Stub>             stub;

};

#endif /* _ROUTER_SPACE_GAME_SERVER_CLIENT_H_ */
