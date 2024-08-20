#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>
#include "Configuration.h"
#include "SplitTool.h"

class WebPage
{
public:
    WebPage(std::string &doc,SplitTool* splittool,int id);
    ~WebPage() {}

    int getDocId();
    std::string getDoc();
    std::map<std::string,int>& getWordsMap();

    friend bool operator==(const WebPage & lhs,const WebPage & rhs);
    friend bool operator<(const WebPage &lhs,const WebPage & rhs);

private:
    void processDoc(const std::string &doc,SplitTool* splittool);

private:
    SplitTool *_splitTool;
    Configuration *_pInstance;
    std::string _doc;// whole file
    int _docId;
    std::string _docTitle;
    std::string _docUrl;
    std::string _docContent;
};

