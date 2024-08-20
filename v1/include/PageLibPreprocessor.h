#pragma once

#include "WebPage.h"
#include "SplitTool.h"
#include "Configuration.h"
#include <unordered_map>

class PageLibPreprocessor
{
public:
    PageLibPreprocessor(SplitTool* splitTool);
    ~PageLibPreprocessor() {}

    void doPreProcess();

private:
    void CreateWebPageLib();
    void cutRedundantPages();
    void buildInvertIndexMap();
    void storeOnDisk();

private:
    Configuration* _pInstance;
    SplitTool *_wordCutter;
    std::unordered_map<int,std::pair<int,int>> _offsetLib;
    std::unordered_map<std::string,std::vector<std::pair<int,double>>> _invertIndexLib;

};

