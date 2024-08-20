#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>
#include <unordered_map>
#include "Configuration.h"
#include "../include/simhash/Simhasher.hpp"

class WebPage
{
public:
    WebPage(std::string &doc,int id,int &pos,
    std::unordered_map<int,std::pair<int,int>> &umap,
    std::vector<uint64_t> &vecOfHash,
    simhash::Simhasher &simhasher);
    ~WebPage() {}

    int getDocId();
    std::string getDoc();
    std::map<std::string,int>& getWordsMap();

    friend bool operator==(const WebPage & lhs,const WebPage & rhs);
    friend bool operator<(const WebPage &lhs,const WebPage & rhs);

private:
    void processDoc(const std::string &doc);

private:
    Configuration *_pInstance;
    std::string _doc;// whole file
    int _docId;
    std::string _docTitle;
    std::string _docUrl;
    std::string _docContent;
};

