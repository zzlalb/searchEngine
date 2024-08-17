#include "../include/DictProducer.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;

string cleanup_str(const string &word){
    string ret;
    for(auto & ele: word){
        if(!ispunct(ele)){
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
    for(auto & ele: _files){
        ifstream ifs;
        ifs.open(ele);

        string word;
        if(ifs.is_open()){
            while(ifs){
                ifs>>word;
                word=cleanup_str(word);
                pushDict(word); 
            }
             
        }else{
            cout<<"open file error in DictProducer::buildEnDict\n";
        }

        ifs.close();
    }

    storeDict("../data/dict.dat");
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

        for(auto & ele: _dict){
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
}



