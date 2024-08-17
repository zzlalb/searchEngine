#pragma once
#include <string>
#include <vector>

class SplitTool
{
public:
    SplitTool() {}
    virtual ~SplitTool() {}

    virtual std::vector<std::string> cut(const std::string & sentence)=0;
};

