#include "../include/Configuration.h"

std::map<std::string,std::string> & Configuration::getConfigMap(){
    return _configs;
}

std::set<std::string> Configuration::getStopWordList(){
    return _stopWordList;
}


Configuration* Configuration::_pInstance=nullptr;
