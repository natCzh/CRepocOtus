#include <fstream>

#include "utils.h"

namespace jsonCommon
{
    bool FillJsonRoot(const std::string &filename, Json::Value &root)
    {
        std::ifstream stream(filename);
        std::string file;
        std::string s;
        if (!stream.is_open())
            return false;

        while (std::getline(stream, s))
            file += s + "\n";

        Json::Reader reader;
        bool success = reader.parse(file, root);
        return success;
    }

    bool FillString(const std::string &filename, std::string &root)
    {
        std::ifstream stream(filename);
        std::string s;
        if (!stream.is_open())
            return false;

        while (std::getline(stream, s))
            root += s + "\n";
        if(root.empty())
            return false;
        if(root[0] == '"')
            root = root.substr(1, root.size()-2);
        return true;
    }

}
