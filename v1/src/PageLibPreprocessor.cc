#include "../include/PageLibPreprocessor.h"
#include <map>
#include <string>
#include <regex>
#include <fstream>

using std::map;
using std::string;
using std::regex;
using std::ofstream;

PageLibPreprocessor::PageLibPreprocessor(SplitTool* splitTool)
{
    _wordCutter=splitTool;
    _pInstance=Configuration::getInstance();
}

void PageLibPreprocessor::CreateWebPageLib(){
    regex pattern("^/home/zzl/searchEngine/v1/conf/peopledaily/.*");
    int id=1;

    

    for(auto & ele: _pInstance->getConfigMap()){
        if(regex_match(ele.second, pattern)){
            ofstream ofs;
            ofs.open("../data/newripepage.dat",std::ios_base::app);

            WebPage pg(ele.second,_wordCutter,id);
            ofs<<pg.getDoc();
            id=pg.getDocId()+1;

            ofs.close();
            ofs.clear();
        }
    }

    
}

void PageLibPreprocessor::storeOnDisk(){
    
}

void PageLibPreprocessor::doPreProcess(){
    CreateWebPageLib();
}