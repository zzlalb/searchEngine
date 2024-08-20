#include <iostream>
#include "../include/PageLibPreprocessor.h"
#include "../include/SplitToolCppJieba.h"

using std::cout;
using std::endl;

void test0(){
    SplitToolCppJieba *jieba=new SplitToolCppJieba();
    PageLibPreprocessor plp(jieba);
    plp.doPreProcess();
}

int main(int argc,char* argv[]){
    test0();

    return 0;

}

