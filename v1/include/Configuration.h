#pragma once

#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <string.h>

class Configuration
{
private:
    Configuration(const std::string &filepath)
    : _configFilePath(filepath)
    {
        std::ifstream ifs(filepath);
        std::string file_body;

        if(ifs.is_open()){
            std::string line;

            while(std::getline(ifs,line)){
                char tmp[100]={0};
                strcpy(tmp,line.c_str());

                _configs[strtok(tmp,"=")]=line.substr(line.find("=")+1);
            }
            
        }else{
            std::cout<<"In Configuration.h open failed\n";
        }
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

private:
    std::string _configFilePath;
    std::map<std::string,std::string> _configs;//This is a map<string,string>
    static Configuration* _pInstance;
};

