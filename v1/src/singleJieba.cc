#include "../include/singleJieba.h"

singleJieba* singleJieba::_pInstance=nullptr;

singleJieba::singleJieba()
: _Jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH)
{

}

singleJieba* singleJieba::getpInstance(){
    if(nullptr==_pInstance){
        _pInstance=new singleJieba();
    }

    return _pInstance;
}

cppjieba::Jieba singleJieba::getjieba(){
    return _Jieba;
}

