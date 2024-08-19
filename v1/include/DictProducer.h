#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include "Configuration.h"
#include "SplitTool.h"

class DictProducer
{
public:
    DictProducer(const std::string &dir);                      //for english
    DictProducer(const std::string &dir,SplitTool *splitTool); //for chinese
    ~DictProducer() {}

    void buildEnDict();                                       
    void buildCnDict();

    void createIndex();

    void storeDict(const char* filepath);             //write dict into filepath
    void showFiles()const;                                    //for test
    void showDict()const;                                     //for test

private:
    void getFiles();                                          //get absolute path(yet unused)
    void pushDict(const std::string& word);
private:
    std::vector<std::string> _files;   //path of corpus
    std::map<std::string,int> _dict; //dictionary; string is word and int is frequency;

    std::vector<std::pair<std::string,int>> _realdict;

    SplitTool *_splitTool;                         //use jieba here
    std::map<std::string,std::set<int>> _index;    // index for dict
};

