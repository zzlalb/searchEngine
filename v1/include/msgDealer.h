#pragma once
#include "./Dictionary.h"

#include <queue>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>

using std::string;
using std::map;
using std::pair;
using std::vector;

struct cmp{
    bool operator()(std::pair<std::string,std::pair<int,int>> &lhs,std::pair<std::string,std::pair<int,int>> &rhs){
        if(lhs.second.first<rhs.second.first){
            return false;
        }else if(lhs.second.first==rhs.second.first){

            if(lhs.second.second<rhs.second.second){
                return false;
            }else if(lhs.second.second==rhs.second.second){
                return lhs.first.c_str()>rhs.first.c_str();
            }else{
                return true;
            }      

        }else{
            return true;
        }
    }
};


class msgDealer
{
public:
    msgDealer(std::string msg,Dictionary* pIns);
    ~msgDealer() {}

    std::vector<std::string> getRecommandWords();

private:
    void mergeSets();
    void buildComparer();
    void fillPQueue();

private:

    std::string _msg;
    Dictionary* _pIns;
    std::set<std::pair<std::string, int>> _rwSet;
    std::map<std::string,std::pair<int,int>> _dictComparer;
    std::priority_queue<pair<string,pair<int,int>>,vector<pair<string,pair<int,int>>>,cmp> _pQueue;
};

