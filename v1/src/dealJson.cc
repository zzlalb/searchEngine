#include "../include/dealJson.h"

using std::string;
using std::vector;
dealJson::dealJson(vector<string> words,int service)
{
    _service=service;
    _words=words;
}

dealJson::dealJson(string page,int service){
    _service=service;
    _page=page;
}

void dealJson::fillJson_object(){
    if(_service==1){
        _json_object.push_back("query");
        for(auto &ele:_words){
            _json_object.push_back(ele);
        }
        
    }else if(_service==2){
        _json_object.push_back("search");
        for(auto &ele:_words){
            _json_object.push_back(ele);
        }
    }
}

string dealJson::returnmsgBuilder(){
    fillJson_object();

    return _json_object.dump();
}

string dealJson::returnPages(){
    _json_object.push_back("search");
    _json_object.push_back(_page);

    return _json_object.dump();
}
