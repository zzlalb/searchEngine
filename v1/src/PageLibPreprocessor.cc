#include "../include/PageLibPreprocessor.h"
#include "../include/simhash/Simhasher.hpp"

#include <map>
#include <string>
#include <regex>
#include <fstream>

using std::map;
using std::string;
using std::regex;
using std::ofstream;

PageLibPreprocessor::PageLibPreprocessor()
{
    _pInstance=Configuration::getInstance();
}

void PageLibPreprocessor::CreateWebPageLib(){
    regex pattern("^/home/zzl/searchEngine/v1/conf/peopledaily/.*");
    using namespace simhash;
        Simhasher simhasher("/home/zzl/searchEngine/v1/include/dict/jieba.dict.utf8", 
                        "/home/zzl/searchEngine/v1/include/dict/hmm_model.utf8", 
                        "/home/zzl/searchEngine/v1/include/dict/idf.utf8", 
                        "/home/zzl/searchEngine/v1/include/dict/stop_words.utf8");
    int id=1;
    int pos=0; 

    for(auto & ele: _pInstance->getConfigMap()){
        if(regex_match(ele.second, pattern)){
            ofstream ofs;
            ofs.open("/home/zzl/searchEngine/v1/data/newripepage.dat",std::ios_base::app);

            WebPage pg(ele.second,id,pos,_offsetLib,_vecOfHash,simhasher);
            ofs<<pg.getDoc();
            id=pg.getDocId()+1;

            ofs.close();
            ofs.clear();
        }
    }

}


void PageLibPreprocessor::storeOnDisk(){
        //create offsetlib
    ofstream ofs;
    ofs.open("/home/zzl/searchEngine/v1/data/newoffset.dat",std::ios_base::app);

    for(auto &ele:_offsetLib){
        ofs<<ele.first<<" "<<ele.second.first<<" "<<ele.second.second<<"\n";
    }

    ofs.close();
    ofs.clear();
}


void PageLibPreprocessor::doPreProcess(){
    CreateWebPageLib();
    storeOnDisk();
}