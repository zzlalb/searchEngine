#pragma once

#include "../include/Configuration.h"
#include "../include/SplitTool.h"
#include "cppjieba/Jieba.hpp" 

class SplitToolCppJieba : public SplitTool
{
public:
    SplitToolCppJieba() {}
    virtual ~SplitToolCppJieba() {}

    virtual std::vector<std::string> cut(const std::string & sentence)=0;

private:
    Configuration * _pInstance;
};

