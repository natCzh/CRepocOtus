#ifndef _AUTHORIZATION_CLASS_H_
#define _AUTHORIZATION_CLASS_H_

#include <map>
#include <atomic>
#include <boost/any.hpp>

#include "IAuthorizationClass.h"

class AuthorizationClass: public IAuthorizationClass
{
public:

    AuthorizationClass(){}

    virtual ~AuthorizationClass(){}

    bool checkAuthorizationObj(unsigned long long idObj, unsigned long long &typeObj) override;
    unsigned long long authorizationObj(unsigned long long typeObj) override;

protected:
    unsigned long long getNextobjId()
    {
        return objIdLast++;
    }

private:
    std::map<unsigned long long, unsigned long long >                                       idObjInf; // храним тип объекта
    static std::atomic<unsigned long long>                                                  objIdLast;
};

#endif /* _AUTHORIZATION_CLASS_H_ */
