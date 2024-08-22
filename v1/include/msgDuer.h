#pragma once
#include "./Dictionary.h"

#include <queue>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>

class msgDuer
{
public:
    msgDuer(std::string msg,Dictionary* pIns);
    ~msgDuer() {}

    std::vector<std::string> getRecommandWords();

    friend bool operator<(std::pair<std::string,int> &lhs,std::pair<std::string,int> &rhs);

private:
    void mergeSets();
    void buildComparer();
    void fillPQueue();

private:
    std::string _msg;
    Dictionary* _pIns;
    set<std::pair<string, int>> _rwSet;
    map<string,std::pair<int,int>> _dictComparer;
    std::priority_queue<std::pair<std::string,int>> _pQueue;
};

