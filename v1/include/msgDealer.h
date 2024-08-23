#pragma once
#include "./Dictionary.h"
#include "./getWebpageLibs.h"

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

struct cmp2{
    bool operator()(pair<int,double>&lhs,pair<int,double>& rhs){
        if(lhs.second<rhs.second){
            return false;
        }else if(lhs.second==rhs.second){
            return lhs.first<rhs.first;
        }else{
            return true;
        }
    }
};

class msgDealer
{
public:
    msgDealer(std::string msg,Dictionary* pIns,getWebpageLibs* pInsweb);
    ~msgDealer() {}

    std::vector<std::string> getRecommandWords();

    vector<string> getRecommandWebPages();

private:
    void mergeSets();
    void buildComparer();
    void fillPQueue();

    void getIntersection();
    void calculateCos();
private:

    std::string _msg;
    Dictionary* _pIns;
    std::set<std::pair<std::string, int>> _rwSet;
    std::map<std::string,std::pair<int,int>> _dictComparer;
    std::priority_queue<pair<string,pair<int,int>>,vector<pair<string,pair<int,int>>>,cmp> _pQueue;

    getWebpageLibs* _pInsWebpage;
    std::set<int> _intersection;
    vector<string> _words;
    std::priority_queue<pair<int,double>,vector<pair<int,double>>,cmp2> _pQueue2;
};

