#pragma once

#include "cppjieba/Jieba.hpp"

class singleJieba
{
private:
    singleJieba();
    ~singleJieba() {}

public:
    static singleJieba* getpInstance();
    cppjieba::Jieba getjieba();

private:
    static singleJieba* _pInstance;
    cppjieba::Jieba _Jieba;
    const char* const DICT_PATH = "../include/dict/jieba.dict.utf8";
    const char* const HMM_PATH = "../include/dict/hmm_model.utf8";
    const char* const USER_DICT_PATH = "../include/dict/user.dict.utf8";
    const char* const IDF_PATH = "../include/dict/idf.utf8";
    const char* const STOP_WORD_PATH = "../include/dict/stop_words.utf8";
};

