#include "../include/Configuration.h"

std::map<std::string,std::string> & Configuration::getConfigMap(){
    return _configs;
}


Configuration* Configuration::_pInstance=nullptr;
