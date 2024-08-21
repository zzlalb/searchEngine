#pragma once

#include "WebPage.h"
#include "Configuration.h"
#include <unordered_map>

class PageLibPreprocessor
{
public:
    PageLibPreprocessor();
    ~PageLibPreprocessor() {}

    void doPreProcess();

private:
    void CreateWebPageLib();;
    void storeOnDisk();

private:
    Configuration* _pInstance;
    std::unordered_map<int,std::pair<int,int>> _offsetLib;
    std::vector<uint64_t> _vecOfHash;

};

