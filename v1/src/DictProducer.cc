#include "../include/DictProducer.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::string;
using std::set;
using std::ifstream;
using std::ofstream;

string cleanup_str(const string &word){
    string ret;
    for(auto & ele: word){
        if((!ispunct(ele))&&(!isdigit(ele))){
            ret+=tolower(ele);
        }
    }
    return ret;
}

DictProducer::DictProducer(const string& dir) 
{
    if(dir!="english.txt"){
        cout<<"dir(filename) error\n";
        exit(1);
    }

    Configuration* pInstance=Configuration::getInstance();
    _files.push_back(pInstance->getConfigMap()[dir]);

}

DictProducer::DictProducer(const string &dir,SplitTool *splitTool)
{
//8.17 write english version first, remain undo
}

void DictProducer::buildEnDict(){
    Configuration* pInstance=Configuration::getInstance();
    set<string> stopwords=pInstance->getStopWordList();

    for(auto & ele: _files){
        ifstream ifs;
        ifs.open(ele);

        string word;
        if(ifs.is_open()){
            while(ifs){
                ifs>>word;
                word=cleanup_str(word);

                if(stopwords.find(word)==stopwords.end()){
                    pushDict(word);
                }
                 
            }

            _dict.erase("");
    
            for(auto &ele: _dict){
                _realdict.push_back(ele);
            }

            _dict.clear();
             
        }else{
            cout<<"open file error in DictProducer::buildEnDict\n";
        }

        ifs.close();
    }

    
    
}

void DictProducer::buildCnDict(){

}

void DictProducer::createIndex(){

}

void DictProducer::storeDict(const char* filepath){
    ofstream ofs(filepath,std::ios::app);

    if(ofs.is_open()){
        string key;
        int value;

        for(auto & ele: _realdict){
            key=ele.first;
            value=ele.second;

            ofs<<key<<" "<<value<<"\n";
        }
    }
}

void DictProducer::showDict()const{

}

void DictProducer::showFiles()const{

}

void DictProducer::getFiles(){

}

void DictProducer::pushDict(const string & word){
    if(_dict.find(word)==_dict.end()){
        _dict.insert({word,1});
    }else{
        ++_dict[word];
    } 

    
    return;
}



