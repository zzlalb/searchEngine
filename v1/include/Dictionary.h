#pragma once
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>

class Dictionary
{
private:
    Dictionary() 
    {
        using std::ifstream;
        using std::string;
        using std::set;
        using std::istringstream;
        using std::cout;

        ifstream ifs1;
        ifs1.open("../data/dict.dat");
        if(ifs1.is_open()){
            string line;
            while(getline(ifs1,line)){
                istringstream iss(line);
                string word;
                int fre;
                iss>>word;
                iss>>fre;
                _dict.push_back({word,fre});
            }
        }else{
            cout<<"open file1 error in Dictionary::Dictionary()\n";
        }

        ifs1.close();
        ifs1.clear();

        ifs1.open("../data/dictcn.dat");
        if(ifs1.is_open()){
            string line;
            while(getline(ifs1,line)){
                istringstream iss(line);
                string word;
                int fre;
                iss>>word;
                iss>>fre;
                _dict.push_back({word,fre});
            }
        }else{
            cout<<"open file2 error in Dictionary::Dictionary()\n";
        }

        ifs1.close();
        ifs1.clear();

        ifstream ifs2;
        ifs2.open("../data/dictIndex.dat");
        if(ifs2.is_open()){
            string line;
            while(getline(ifs2,line)){
                istringstream iss(line);
                string word;
                set<int> indexset;

                iss>>word;
                while(iss){
                    int index;
                    iss>>index;
                    indexset.insert(index);
                }

                _index[word]=indexset;
            }
        }else{
            cout<<"open file3 error in Dictionary::Dictionary()\n";
        }

        ifs2.close();
        ifs2.clear();

    }
    ~Dictionary() {}

public:
    static Dictionary* getInstance();
    std::vector<std::pair<std::string,int>> &getDict();
    std::map<std::string,std::set<int>> &getIndex();

private:
    std::vector<std::pair<std::string,int>> _dict;
    std::map<std::string,std::set<int>> _index;
    static Dictionary* _pInstance;
};

