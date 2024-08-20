#include "../include/WebPage.h"
#include "../include/SplitTool.h"
#include "../include/tinyxml2.h"
#include <fstream>
#include <iostream>

using namespace tinyxml2;
using std::cout;
using std::string;
using std::vector;

size_t nBytesCode(const char ch){
    if(ch&(1<<7)){
        int nBytes=1;
        for(int idx=0;idx!=6;++idx){
            if(ch&(1<<(6-idx))){
                ++nBytes;
            }else{
                break;
            }
        }
        return nBytes;
    }
    return 1;
}

string cleanup_cnPage(const string &page){
    string ret;
    for(size_t i=0;i<page.size();){
        int len=nBytesCode(page[i]);
        if(len==1){
            ++i;
        }else{
            for(int j=0;j<len;++j){
                ret.push_back(page[i+j]);
            }
            i+=len;
        }
    }
    return ret;
}

WebPage::WebPage(string &doc,SplitTool* splitTool,int id)
{
    _splitTool=splitTool;
    _pInstance=Configuration::getInstance();
    _docId=id;

    XMLDocument xmldoc;
    xmldoc.LoadFile(doc.c_str());

    XMLElement *root=xmldoc.RootElement();

    XMLElement *child=root->FirstChildElement("channel")->FirstChildElement("item");

    

    while(child!=nullptr){
        _docTitle=child->FirstChildElement("title")->GetText();
        
        //cout<<"\n";
        _docUrl=child->FirstChildElement("link")->GetText();
        _docContent=child->FirstChildElement("description")->GetText();
        _docContent=cleanup_cnPage(_docContent);

        // vector<string> text=_splitTool->cut(_docContent);
        // for(auto &ele:text){
        //     cout<<ele<<" ";
        // }

        string page = "<doc>\n<docid>" + std::to_string(_docId) +        
                        "</docid>\n<title>" + _docTitle+
                        "</title>\n<url>" +_docUrl + 
                        "</url>\n<content>" + _docContent +                                                  
                        "</content>\n</doc>"+"\n";

        _doc.append(page);

        child=child->NextSiblingElement();
        ++_docId;
    }

}

int WebPage::getDocId(){
    return _docId;
}

std::string WebPage::getDoc(){
    return _doc;
}