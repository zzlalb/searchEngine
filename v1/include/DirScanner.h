#pragma once

#include <vector>
#include <string>
#include "Configuration.h"

class DirScanner
{
public:
    DirScanner();
    ~DirScanner() {}

    void operator()();
    
    std::vector<std::string> &getFiles();

    void traverse(const std::string & dirname);

private:
    std::vector<std::string> _files;
};

