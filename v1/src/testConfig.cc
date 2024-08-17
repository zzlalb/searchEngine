#include <iostream>

#include "../include/Configuration.h"

using std::cout;
using std::string;
using std::map;

Configuration* pins=Configuration::getInstance();

map<string,string> configmap=pins->getConfigMap();

int main(void){
    for(auto &ele: configmap){
        cout<<ele.first<<" "<<ele.second<<"\n";
    }

    return 0;
}
