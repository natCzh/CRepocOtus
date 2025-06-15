#ifndef _I_LOGGER_H_
#define _I_LOGGER_H_

#include <string>

class ILogger
{
public:
    virtual ~ILogger(){}

    std::string logProcess();

};

#endif /* _I_LOGGER_H_ */
