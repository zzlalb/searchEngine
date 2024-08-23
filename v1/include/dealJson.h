#pragma once

#include "nlohmann/json.hpp"
#include <vector>
#include <string>
#include <iostream>

class dealJson
{
public:
    dealJson(std::vector<std::string>,int);
    dealJson(std::string,int);
    ~dealJson() {}

    void fillJson_object();
    std::string returnmsgBuilder();
    std::string returnPages();

private:
    int _service;
    std::vector<std::string> _words;
    nlohmann::json _json_object;
    std::string _page;
};

