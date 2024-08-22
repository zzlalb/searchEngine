#include "../include/dealJson.h"

using std::string;
using std::vector;
dealJson::dealJson(vector<string> words)
{
    _words=words;
}

void dealJson::fillJson_object(){
    nlohmann::json childObject;
    for(auto &ele:_words){
        childObject.push_back(ele);
    }
    
    _json_object["query"]=childObject;
}

string dealJson::returnmsgBuilder(){
    fillJson_object();

    return _json_object.dump();
}