#include <iostream>
#include "../include/DictProducer.h"
#include "../include/SplitToolCppJieba.h"

using std::cout;
using std::endl;

void test0(){
    SplitToolCppJieba* jieba=new SplitToolCppJieba();
    DictProducer dp("art",jieba);

    //dp.showFiles();
    dp.buildCnDict();

    dp.storeDict("../data/dictcn.dat");
}

int main(int argc,char* argv[]){
    test0();

    return 0;

}

