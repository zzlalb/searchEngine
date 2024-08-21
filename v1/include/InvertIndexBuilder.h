#pragma once

#include "cppjieba/Jieba.hpp"
#include <unordered_map>
#include <set>
#include <string>
#include <vector>

class InvertIndexBuilder
{
public:
    InvertIndexBuilder() {}
    ~InvertIndexBuilder() {}

    void iilibBuilder();

private:
    std::unordered_map<int,std::pair<int,int>> _offsetLib;
    std::unordered_map<std::string,std::set<std::pair<int,double>>> _invertIndexLib;
};

