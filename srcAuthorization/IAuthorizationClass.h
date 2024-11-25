#ifndef _I_AUTHORIZATION_CLASS_H_
#define _I_AUTHORIZATION_CLASS_H_

class IAuthorizationClass
{
public:

    virtual ~IAuthorizationClass(){}

    virtual bool checkAuthorizationObj(unsigned long long idObj, unsigned long long &typeObj) = 0;
    virtual unsigned long long authorizationObj(unsigned long long typeObj) = 0;
};

#endif /* _I_AUTHORIZATION_CLASS_H_ */
