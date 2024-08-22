#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>

#include "../include/Dictionary.h"

using std::string;
using std::map;
using std::vector;
using std::set;
using std::cout;
using std::endl;

void test0(){
    Dictionary* pins=Dictionary::getInstance();
    vector<std::pair<string,int>> tmpVec=pins->getDict();
    map<string,set<int>> tmpIndex=pins->getIndex();

    // string key;
    // int value;
    // for(auto & ele: tmpVec){
    //     key=ele.first;
    //     value=ele.second;

    //     cout<<key<<" "<<value<<"\n";
    // }

    for(auto &ele:tmpIndex){
        cout<<ele.first<<" ";
        for(auto &sets: ele.second){
            cout<<sets<<" ";
        }
        cout<<"\n";
    }
}

int main(int argc,char* argv[]){
    test0();

    return 0;

}

