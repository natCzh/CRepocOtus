#ifndef _LOGGER_VISITOR_H_
#define _LOGGER_VISITOR_H_

#include <string>
#include <map>
#include <vector>
#include <memory>

class LoggerVisitor
{
public:

    virtual std::vector<std::map<std::string, int> > ParseLogData(const std::string &logData) = 0;

};

#endif /* _LOGGER_VISITOR_H_ */
