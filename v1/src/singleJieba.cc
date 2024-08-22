#include "../include/singleJieba.h"

singleJieba* singleJieba::_pInstance=nullptr;

singleJieba* singleJieba::getpInstance(){
    if(nullptr==_pInstance){
        _pInstance=new singleJieba();
    }

    return _pInstance;
}

cppjieba::Jieba singleJieba::getjieba(){
    return _jieba;
}

