#pragma once
#include "DirScanner.h"
#include <map>
#include "Configuration.h"

class PageLib
{
public:
    PageLib(Configuration &conf,DirScanner & dirScanner,FileProcessor& fileProcessor);
    ~PageLib() {}

    void create();
    void store();

private:
    DirScanner &_dirScanner;
    std::vector<std::string> _pages;
    std::map<int,std::pair<int,int>> _offsetLib;

};

