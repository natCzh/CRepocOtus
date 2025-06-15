#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include "json.h"

namespace jsonCommon
{
    bool FillJsonRoot(  const std::string &filename, Json::Value &root );
    bool FillString(  const std::string &filename, std::string &root );
}
#endif /* UTILS_H_ */