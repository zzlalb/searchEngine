#pragma once

#include <string>
#include "nlohmann/json.hpp"

class ProtocolParser
{
public:
    ProtocolParser(const std::string&);
    ~ProtocolParser() {}

    int judgeService();

private:
    std::string _msg;
};

