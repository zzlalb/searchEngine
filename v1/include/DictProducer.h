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

    void storeDict(const std::string & filepath);             //write dict into filepath
    void showFiles()const;                                    //for test
    void showDict()const;                                     //for test

private:
    void getFiles();                                          //get absolute path
    void pushDict(const std::string& word);
private:
    std::vector<std::string> _files;   //path of corpus
    std::vector<std::pair<std::string,int>> _dict; //dictionary

    SplitTool *_splitTool;                         //use jieba here
    std::map<std::string,std::set<int>> _index;    // index for dict
};

