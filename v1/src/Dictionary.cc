#include "../include/Dictionary.h"

Dictionary* Dictionary::_pInstance=nullptr;

Dictionary* Dictionary::getInstance(){
    if(nullptr==_pInstance){
        _pInstance=new Dictionary();
    }

    return _pInstance;
}

std::vector<std::pair<std::string,int>> &Dictionary::getDict(){
    return _dict;
}

std::map<std::string,std::set<int>> & Dictionary::getIndex(){
    return _index;
}