#ifndef _I_ROUTER_MAIN_CLASS_H_
#define _I_ROUTER_MAIN_CLASS_H_

#include <string>

class IRouterMainClass
{
public:
    virtual ~IRouterMainClass(){}

    virtual unsigned long long AuthorizationObj(size_t typeRegister) = 0;

    // [out] result bool
    // [in - out] typeObj
    virtual bool StartNewGame(unsigned long long idObj, const std::string &idOtherObj, const std::string &otherArgs, unsigned long long &typeObj) = 0;

    virtual bool AddCommandGame(unsigned long long idSender, unsigned long long idGame, unsigned long long idObj, const std::string &TypeCommand, const std::string &args) = 0;

    virtual bool StopGame(unsigned long long idSender, unsigned long long idGame) = 0;

    // [in-out] infGame - информация об игре
    virtual void GetInfGame(unsigned long long idGame, std::string &infGame) = 0;
};

#endif /* _I_ROUTER_MAIN_CLASS_H_ */
