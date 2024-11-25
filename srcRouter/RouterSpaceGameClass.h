#ifndef _ROUTER_SPACE_GAME_CLASS_H_
#define _ROUTER_SPACE_GAME_CLASS_H_

#include <string>
#include <memory>

#include <grpc/grpc.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

using grpc::ClientAsyncReaderWriter;
using grpc::Channel;

class RouterSpaceGameClass
{
public:

    RouterSpaceGameClass(){}

    virtual ~RouterSpaceGameClass(){}


     void connectToServer(const std::string &serverAddress);

protected:
     void processingFunction();
\

private:

    std::string m_serverAdderess;

};

#endif /* _ROUTER_SPACE_GAME_CLASS_H_ */
