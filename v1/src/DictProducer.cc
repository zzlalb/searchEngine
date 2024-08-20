#include "../include/DictProducer.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using std::cout;
using std::string;
using std::set;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::regex;

string cleanup_str(const string &word){
    string ret;
    for(auto & ele: word){
        if((!ispunct(ele))&&(!isdigit(ele))){
            ret+=tolower(ele);
        }
    }
    return ret;
}

size_t nBytesCode(const char ch){
    if(ch&(1<<7)){
        int nBytes=1;
        for(int idx=0;idx!=6;++idx){
            if(ch&(1<<(6-idx))){
                ++nBytes;
            }else{
                break;
            }
        }
        return nBytes;
    }
    return 1;
}

string cleanup_cnPage(const string &page){
    string ret;
    for(size_t i=0;i<page.size();){
        int len=nBytesCode(page[i]);
        if(len==1){
            ++i;
        }else{
            for(int j=0;j<len;++j){
                ret.push_back(page[i+j]);
            }
            i+=len;
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
//8.18 finished
    Configuration* pInstance=Configuration::getInstance();
    _splitTool=splitTool;

    if(dir=="art"){
        regex pattern("^/home/zzl/searchEngine/v1/conf/art/.*");

        for(auto & ele: pInstance->getConfigMap()){
            if(regex_match(ele.second, pattern)){
                _files.push_back(ele.second);
            }
        }
    }
      
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
    Configuration* pInstance=Configuration::getInstance();
    set<string> stopwords=pInstance->getStopWordList();

    for(auto &ele: _files){
        ifstream ifs;
        ifs.open(ele);

        if (!ifs.is_open()){
            cout << "open file error in DictProducer::buildCnDict\n";
        }else{
            string page;
            string line;
            while (getline(ifs, line)){
                page.append(line);
            }

            page=cleanup_cnPage(page);

            vector<string> splitted = _splitTool->cut(page);

            for (auto &ele : splitted){
                if (stopwords.find(ele) == stopwords.end()){
                    pushDict(ele);
                }
            }           
        }
       
        ifs.close();
        ifs.clear();
    }

    for (auto &ele : _dict){
        _realdict.push_back(ele);
    }

    _dict.clear();
}

void DictProducer::createIndex(){
    ifstream ifs1("/home/zzl/searchEngine/v1/data/dict.dat");
    ifstream ifs2("/home/zzl/searchEngine/v1/data/dictcn.dat");

    for(int i=0;i<26;++i){
        string alp;
        alp.push_back('a'+i);
        //cout<<alp<<" ";
        _index[alp]=set<int>();
    }

    if(ifs1.is_open()&&ifs2.is_open()){
        string line;
        while (getline(ifs1, line)){
            string key;
            int value;
            ifs1>>key;
            ifs1>>value;

            //cout<<key<<" "<<value<<"\n";

            _realdict.push_back({key,value});
        }
        ifs1.close();
        ifs1.clear();

        while (getline(ifs2, line)){
            string key;
            int value;
            ifs2>>key;
            ifs2>>value;
            //cout<<key<<" "<<value<<"\n";
            _realdict.push_back({key,value});
        }
        ifs2.close();
        ifs2.clear();    

        for(int i=0;i<_realdict.size();++i){
            for(int j=0;j<_realdict[i].first.size();){
                int len=nBytesCode(_realdict[i].first[j]);
                if(len==1){
                    string tmp;
                    tmp.push_back(_realdict[i].first[j]);
                    _index[tmp].insert(i);
                    ++j;
                }else{
                    string ch;
                    for(int k=0;k<len;++k){
                        ch.push_back(_realdict[i].first[j+k]);
                    }
                    j+=len;
                    _index[ch].insert(i);
                }                
            }           
        }   
        
        ofstream ofs;
        ofs.open("/home/zzl/searchEngine/v1/data/dictIndex.dat",std::ios_base::app);

        for(auto &ele:_index){
            ofs<<ele.first<<" ";
            for(auto &cha:ele.second){
                ofs<<cha<<" ";
            }
            ofs<<"\n";
        }

    }
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
    for(auto &ele:_realdict){
        cout<<ele.first<<" "<<ele.second<<"\n";
    }
}

void DictProducer::showFiles()const{
    for(auto & ele: _files){
        cout<<ele<<"\n";
    }
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



