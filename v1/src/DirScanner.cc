#include "../include/DirScanner.h"
#include <regex>

using std::string;
using std::vector;
using std::regex;

DirScanner::DirScanner(){}

void DirScanner::traverse(const string & dirname){
    if(dirname!="peopledaily"){
        return;
    }

    Configuration* pIns=Configuration::getInstance();

    regex pattern("^/home/zzl/searchEngine/v1/conf/peopledaily/.*");

    for(auto &ele:pIns->getConfigMap()){
        if(regex_match(ele.second, pattern)){
            _files.push_back(ele.second);
        }
    }
}

void DirScanner::operator()(){
    traverse("peopledaily");
}

vector<string> & DirScanner::getFiles(){
    return _files;
}