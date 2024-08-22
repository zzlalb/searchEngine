#pragma once

#include "nlohmann/json.hpp"
#include <vector>
#include <string>
#include <iostream>

class dealJson
{
public:
    dealJson(std::vector<std::string>);
    ~dealJson() {}

    void fillJson_object();
    std::string returnmsgBuilder();

private:
    std::vector<std::string> _words;
    nlohmann::json _json_object;
};

