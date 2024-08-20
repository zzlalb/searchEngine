#include <iostream>
#include "../include/DirScanner.h"

using std::cout;
using std::endl;

void test0(){
    DirScanner ds;
    ds();

    for(auto &ele:ds.getFiles()){
        cout<<ele<<"\n";
    }
}

int main(int argc,char* argv[]){
    test0();

    return 0;

}

