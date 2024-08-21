#include "../include/InvertIndexBuilder.h"
#include "../include/Configuration.h"

#include <math.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <set>
#include <iostream>

using std::cout;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::unordered_map;
using std::string;
using std::vector;
using std::map;
using std::set;

void InvertIndexBuilder::iilibBuilder(){
    Configuration* pInstance=Configuration::getInstance();
    set<string> stopwords=pInstance->getStopWordList();

    const char* const DICT_PATH = "../include/dict/jieba.dict.utf8";
    const char* const HMM_PATH = "../include/dict/hmm_model.utf8";
    const char* const USER_DICT_PATH = "../include/dict/user.dict.utf8";
    const char* const IDF_PATH = "../include/dict/idf.utf8";
    const char* const STOP_WORD_PATH = "../include/dict/stop_words.utf8";

    cppjieba::Jieba jieba(DICT_PATH,
                      HMM_PATH,
                      USER_DICT_PATH,
                      IDF_PATH,
                      STOP_WORD_PATH);

    ifstream ifs1;
    ifstream ifs2;
    ifs1.open("/home/zzl/searchEngine/v1/data/newripepage.dat");
    ifs2.open("/home/zzl/searchEngine/v1/data/newoffset.dat");

    string line;
    while(getline(ifs2,line)){
        int docid;
        int pos;
        int size;

        istringstream iss(line);
        iss>>docid;
        iss>>pos;
        iss>>size;

        _offsetLib[docid]={pos,size};
    }

    int veclen=_offsetLib.size();

    map<string,set<int>> allPageFreSaver;
    vector<map<string,int>> thisPageFreSaverSaver;

    for(int i=0;i<veclen;++i){
        int size=_offsetLib[i].second;

        char buf[size+1];
        memset(buf,0,size+1);
        
        ifs1.seekg(_offsetLib[i].first);
        ifs1.read(buf,size);

        string page=buf;
        vector<string> words;
        jieba.Cut(page,words,true);

        string realpage;
        map<string,int> thisPageFreSaver;

        for(auto &ele: words){
            if (stopwords.find(ele) == stopwords.end()){
                realpage.append(ele);

                if(thisPageFreSaver.find(ele)==thisPageFreSaver.end()){
                    thisPageFreSaver.insert({ele,1});
                }else{
                    ++thisPageFreSaver[ele];
                } 

                if(allPageFreSaver.find(ele)==allPageFreSaver.end()){
                    allPageFreSaver.insert({ele,{i}});
                }else{
                    allPageFreSaver[ele].insert(i);
                } 
            }
        }
        cout<<"%"<<(((double)i+1)/(double)veclen)*100<<"\n";
        thisPageFreSaverSaver.push_back(thisPageFreSaver);
    }

    /*for test. no prob*/
    // for(auto &ele:allPageFreSaver){
    //     cout<<ele.first<<" ";
    //     for(auto &sets:ele.second){
    //         cout<<sets<<" ";
    //     }
    //     cout<<"\n";
    // }

    int pagenum=thisPageFreSaverSaver.size();

    /*for test no prob*/
    // for(int i=0;i<pagenum;++i){
    //     for(auto &ele:thisPageFreSaverSaver[i]){
    //         cout<<ele.first<<" "<<ele.second<<"\n";
    //     }
    // }

    unordered_map<string,set<std::pair<int,double>>> tmpInvert;
    double wT=0;

    for(auto &ele:allPageFreSaver){
        double df=ele.second.size();

        for(int i=0;i<pagenum;++i){
            map<string,int> &tmp=thisPageFreSaverSaver[i];
            if(tmp.find(ele.first)!=tmp.end()){
                double tf=tmp[ele.first];
                double idf=log2((double)pagenum/(df+1));

                double w=tf*idf;
                wT+=w*w;

                tmpInvert[ele.first].insert({i,w});
            }
        }
    }

    /*for test no prob*/
    // cout<<"hello\n";
    // for(auto & ele:tmpInvert){
    //     cout<<ele.first<<" ";
    //     for(auto &sets:ele.second){
    //         cout<<sets.first<<" "<<sets.second<<" ";
    //     }
    //     cout<<"\n";
    // }

    wT=sqrt(wT);
    for(auto &ele:tmpInvert){
        for(auto & sets:ele.second){
            if(_invertIndexLib.find(ele.first)==_invertIndexLib.end()){
                _invertIndexLib[ele.first]={{sets.first,sets.second/wT}};
            }else{
                _invertIndexLib[ele.first].insert({sets.first,sets.second/wT});
            }
            
        }
    }

    ofstream ofs;
    ofs.open("/home/zzl/searchEngine/v1/data/invertIndex.dat",std::ios_base::app);

    for(auto &ele: _invertIndexLib){
        ofs<<ele.first<<" ";
        for(auto &sets:ele.second){
            ofs<<sets.first<<" "<<sets.second<<" ";
        }
        ofs<<"\n";
    }
}