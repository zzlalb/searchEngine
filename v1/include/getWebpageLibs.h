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
private:
    getWebpageLibs() 
    {
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
                //cout<<docid<<" "<<pos<<" "<<size<<"\n";
            }
        }else{
            cout<<"open file1 error in getWebpageLibs\n";
        }

        ifs1.close();

        ifstream ifs2;
        ifs2.open("../data/invertIndex.dat");
        if(ifs2.is_open()){
            string line;
            while(getline(ifs2,line)){
                string word;
                int docid;
                double weight;

                istringstream iss(line);
                iss>>word;

                set<std::pair<int,double>> tmpset;
                while(iss){
                    iss>>docid;
                    iss>>weight;

                    tmpset.insert({docid,weight});
                }   

                _invertLib[word]=tmpset;
                //cout<<word<<" ";
            }
        }else{
            cout<<"open file2 error in getWebpageLibs\n";
        }

        ifs2.close();

    }

    ~getWebpageLibs() {}

public:
    static getWebpageLibs* getInstance();
    std::unordered_map<std::string,std::set<std::pair<int,double>>> &getInvertlib();
    std::unordered_map<int,std::pair<int,int>> &getOffsetlib();

private:
    static getWebpageLibs* _pIns;
    std::unordered_map<std::string,std::set<std::pair<int,double>>> _invertLib;//<word,<docid,weight>>
    std::unordered_map<int,std::pair<int,int>> _offsetLib;//<pos,length>
};

