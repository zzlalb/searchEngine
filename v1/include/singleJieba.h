#pragma once

#include "cppjieba/Jieba.hpp"

class singleJieba
{
    const char* const DICT_PATH = "/home/zzl/searchEngine/v1/include/dict/jieba.dict.utf8";
    const char* const HMM_PATH = "/home/zzl/searchEngine/v1/include/dict/hmm_model.utf8";
    const char* const USER_DICT_PATH = "/home/zzl/searchEngine/v1/include/dict/user.dict.utf8";
    const char* const IDF_PATH = "/home/zzl/searchEngine/v1/include/dict/idf.utf8";
    const char* const STOP_WORD_PATH = "/home/zzl/searchEngine/v1/include/dict/stop_words.utf8";
private:
    singleJieba()
    : _jieba(DICT_PATH,
                      HMM_PATH,
                      USER_DICT_PATH,
                      IDF_PATH,
                      STOP_WORD_PATH)
    {

    }
    ~singleJieba() {}

public:
    static singleJieba* getpInstance();
    cppjieba::Jieba getjieba();

private:
    static singleJieba* _pInstance;
    
    cppjieba::Jieba _jieba;
   
};

