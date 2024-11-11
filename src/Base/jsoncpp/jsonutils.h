#ifndef JSONUTILS_H
#define JSONUTILS_H

#include <string>

namespace Json {
    class Value;
}

class JsonSerializable
{
    std::string typeName;
public:
    virtual ~JsonSerializable() {}
    JsonSerializable(const std::string &tn)
        : typeName(tn)
    {}
    virtual const std::string& name() const {return typeName;}
    virtual bool read(const Json::Value &jsonObj) = 0;
    virtual void write(Json::Value &jsonObj) const = 0;
    virtual bool isValid() const = 0;
};

#endif // JSONUTILS_H
