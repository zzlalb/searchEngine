#include <iostream>
#include "../include/WebPage.h"
#include "../include/SplitToolCppJieba.h"
#include <string>

using std::string;
using std::cout;
using std::endl;

void test0(){
    SplitToolCppJieba *jieba=new SplitToolCppJieba();
    string str("/home/zzl/searchEngine/v1/conf/peopledaily/cpc.xml");
    WebPage pg(str,jieba,1);   

}

int main(int argc,char* argv[]){
    test0();

    return 0;

}

