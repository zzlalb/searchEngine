#include "../include/Dictionary.h"

Dictionary* Dictionary::getInstance(){
    if(nullptr==_pInstance){
        _pInstance=new Dictionary();
    }
}