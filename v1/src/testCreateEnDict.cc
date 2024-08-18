#include <iostream>
#include "../include/DictProducer.h"

using std::cout;
using std::endl;

void test0(){
    DictProducer dp("english.txt");

    dp.buildEnDict();

    dp.storeDict("../data/dict.dat");

}

int main(int argc,char* argv[]){
    test0();

    return 0;

}

