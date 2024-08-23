#pragma once

#include <string>
#include "nlohmann/json.hpp"

class ProtocolParser
{
public:
    ProtocolParser(const std::string&);
    ~ProtocolParser() {}

    int judgeService();

    std::string getNewmsg();

private:
    std::string _msg;
    std::string _newmsg;
};

