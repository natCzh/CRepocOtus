#include "AuthorizationClass.h"

std::atomic<unsigned long long> AuthorizationClass::objIdLast(0);

bool AuthorizationClass::checkAuthorizationObj(unsigned long long idObj, unsigned long long &typeObj)
{
    auto iter = idObjInf.find(idObj);
    if (iter != idObjInf.end())
    {
        typeObj = iter->second;
        return true;
    }
    return false;
}

unsigned long long AuthorizationClass::authorizationObj(unsigned long long typeObj)
{
    unsigned long long idObjCur = getNextobjId();
    idObjInf[idObjCur] = typeObj;
    return idObjCur;
}
