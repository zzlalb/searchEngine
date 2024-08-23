#include "../include/ProtocolParser.h"
#include <iostream>

using std::string;
using std::cout;

ProtocolParser::ProtocolParser(const string &msg){
    _msg=msg;
}

int ProtocolParser::judgeService(){
    
    //cout<<_msg.c_str()<<"\n";
    nlohmann::json json_object=nlohmann::json::parse(_msg.c_str());

    if(json_object[1][0]=="query"){
        return 1;
    }else if(json_object[1][0]=="search"){
        return 2;
    }

    return -1;
}