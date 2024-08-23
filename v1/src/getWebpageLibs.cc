#include "../include/getWebpageLibs.h"

getWebpageLibs* getWebpageLibs::_pIns=nullptr;

getWebpageLibs* getWebpageLibs::getInstance(){
    if(nullptr==_pIns){
        _pIns=new getWebpageLibs();
    }

    return _pIns;
}

std::unordered_map<std::string,std::set<std::pair<int,double>>> &getWebpageLibs::getInvertlib(){
    return _invertLib;
}

std::unordered_map<int,std::pair<int,int>> &getWebpageLibs::getOffsetlib(){
    return _offsetLib;
}