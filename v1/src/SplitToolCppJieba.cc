#include "../include/SplitToolCppJieba.h"

const char* const DICT_PATH = "../include/dict/jieba.dict.utf8";
const char* const HMM_PATH = "../include/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../include/dict/user.dict.utf8";
const char* const IDF_PATH = "../include/dict/idf.utf8";
const char* const STOP_WORD_PATH = "../include/dict/stop_words.utf8";

std::vector<std::string> SplitToolCppJieba::cut(const std::string & sentence){
    cppjieba::Jieba jieba(DICT_PATH,
                      HMM_PATH,
                      USER_DICT_PATH,
                      IDF_PATH,
                      STOP_WORD_PATH);

    std::vector<std::string> words;
    jieba.Cut(sentence,words,true);

    return words;
}


