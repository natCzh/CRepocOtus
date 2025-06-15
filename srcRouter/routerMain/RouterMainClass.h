#ifndef _ROUTER_MAIN_CLASS_H_
#define _ROUTER_MAIN_CLASS_H_

#include <memory>

#include "authorization/RouterAuthorizationClient.h"
#include "serverGame/RouterSpaceGameServerClient.h"

#include "routerMain/IRouterMainClass.h"

class RouterMainClass: public IRouterMainClass
{
public:

    RouterMainClass(RouterAuthorizationClient* authorClient_, RouterSpaceGameServerClient* spaceGameClient_)
        : authorClient(authorClient_)
        , spaceGameClient(spaceGameClient_)
    {}

    virtual ~RouterMainClass(){}

    // [out] idObj
    unsigned long long AuthorizationObj(size_t typeRegister);

    // [out] result bool
    // [in - out] typeObj
    bool StartNewGame(unsigned long long idObj, const std::string &idOtherObj, const std::string &otherArgs, unsigned long long &typeObj);

    bool AddCommandGame(unsigned long long idSender, unsigned long long idGame, unsigned long long idObj, const std::string &TypeCommand, const std::string &args);

    bool StopGame(unsigned long long idSender, unsigned long long idGame);

    // [in-out] infGame - информация об игре
    void GetInfGame(unsigned long long idGame, std::string &infGame);

private:

    RouterAuthorizationClient* authorClient;
    RouterSpaceGameServerClient* spaceGameClient;
};

#endif /* _ROUTER_MAIN_CLASS_H_ */
