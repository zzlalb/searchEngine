#pragma once

#include "../include/Configuration.h"
#include "../include/SplitTool.h"
#include "cppjieba/Jieba.hpp" 

class SplitToolCppJieba : public SplitTool
{
public:
    SplitToolCppJieba(){}
    virtual ~SplitToolCppJieba() {}

    std::vector<std::string> cut(const std::string & sentence);

private:
    Configuration * _pInstance;
};

