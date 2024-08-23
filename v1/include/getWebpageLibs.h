#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>

class getWebpageLibs
{
public:
    getWebpageLibs() {
        using std::unordered_map;
        using std::ifstream;
        using std::string;
        using std::set;
        using std::istringstream;
        using std::cout;

        ifstream ifs1;
        ifs1.open("../data/newoffset.dat");
        if(ifs1.is_open()){
            string line;
            while(getline(ifs1,line)){
                int docid;
                int pos;
                int size;

                istringstream iss(line);
                iss>>docid;
                iss>>pos;
                iss>>size;

                _offsetLib[docid]={pos,size};
            }
        }else{
            cout<<"open file1 error in Dictionary::Dictionary()\n";
        }

        ifs1.close();

        ifstream ifs2;

    }
    ~getWebpageLibs() {}

private:
    std::unordered_map<std::string,std::set<std::pair<int,double>>> _invertLib;//<word,<docid,weight>>
    std::unordered_map<int,std::pair<int,int>> _offsetLib;//<pos,length>
};

