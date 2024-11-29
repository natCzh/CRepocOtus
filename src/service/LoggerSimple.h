#ifndef _LOGGER_SIMPLE_H_
#define _LOGGER_SIMPLE_H_

#include "IoC/IoC.h"
#include "service/ILogger.h"
#include "CommonLib/UObject.h"

extern IoC* ioc;
class LoggerSimple: public ILogger
{
public:
    LoggerSimple(){}

    virtual ~LoggerSimple(){}

    std::string logProcess()
    {
        std::string logStr;

        std::unordered_map<unsigned long long, UObject_Ptr> obj = ioc->Resolve<std::unordered_map<unsigned long long, UObject_Ptr> >("GameItems");

        for (auto iter = obj.begin(); iter != obj.end(); iter++)
        {
            std::string logObg = std::to_string(iter->first) + ",";
            boost::any valAny = iter->second->getProperty("position_x");
            int valInt = boost::any_cast<int>(valAny);
            logObg += std::to_string(valInt);
            logObg += ",";
            valAny = iter->second->getProperty("position_y");
            valInt = boost::any_cast<int>(valAny);
            logObg += std::to_string(valInt);
            logObg += ",";
            valAny = iter->second->getProperty("numberShot");
            valInt = boost::any_cast<int>(valAny);
            logObg += std::to_string(valInt);
            logObg += ";";

            logStr += logObg;
        }
        return logStr;
    }
};

#endif /* _LOGGER_SIMPLE_H_ */
