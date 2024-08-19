#pragma once

#include <string>
#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <string.h>

class Configuration
{
private:
    Configuration(const std::string &filepath)
    : _configFilePath(filepath)
    {
        //make config map
        std::ifstream ifs(filepath);
        std::string file_body;

        if(ifs.is_open()){
            std::string line;

            while(std::getline(ifs,line)){
                char tmp[100]={0};
                strcpy(tmp,line.c_str());

                _configs[strtok(tmp,"=")]=line.substr(line.find("=")+1);
            }
            ifs.close();

        }else{
            std::cout<<"In Configuration.h open english.txt failed\n";
        }

        //make stopword list
        std::ifstream ifs2("/home/zzl/searchEngine/v1/conf/stop_words_eng.txt");
        std::string stopword;
        if(ifs2.is_open()){
            while(ifs2){
                ifs2>>stopword;
                _stopWordList.insert(stopword);
            }
        }else{
            std::cout<<"In Configuration.h open stopList failed\n";
        }

        std::ifstream ifs3("/home/zzl/searchEngine/v1/conf/stop_words_zh.txt");
        if(ifs3.is_open()){
            while(ifs3){
                ifs3>>stopword;
                _stopWordList.insert(stopword);
            }
        }else{
            std::cout<<"In Configuration.h open stopList failed\n";
        }

        ifs2.close();
        ifs3.close();
    }

    ~Configuration() {}

public:
    static Configuration* getInstance(){
        if(nullptr==_pInstance){
            _pInstance=new Configuration("../conf/myconf.conf");
        }

        return _pInstance;
    }

    std::map<std::string,std::string> & getConfigMap();
    std::set<std::string> getStopWordList();

private:
    std::string _configFilePath;
    std::map<std::string,std::string> _configs;//This is a map<string,string>
    std::set<std::string> _stopWordList;
    static Configuration* _pInstance;
};

