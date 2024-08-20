#include "../include/WebPage.h"
#include "../include/tinyxml2.h"

#include <fstream>
#include <iostream>

using namespace tinyxml2;
using std::cout;
using std::string;
using std::vector;
using std::unordered_map;

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

WebPage::WebPage(string &doc,int id,int &pos,unordered_map<int,std::pair<int,int>> &umap,std::vector<uint64_t> &vecOfHash,simhash::Simhasher &simhasher)
{
    _pInstance=Configuration::getInstance();
    _docId=id;

    using namespace simhash;


    XMLDocument xmldoc;
    xmldoc.LoadFile(doc.c_str());

    XMLElement *root=xmldoc.RootElement();

    XMLElement *child=root->FirstChildElement("channel")->FirstChildElement("item"); 

    while(child!=nullptr){
        _docTitle=child->FirstChildElement("title")->GetText();
        
        _docUrl=child->FirstChildElement("link")->GetText();
        _docContent=child->FirstChildElement("description")->GetText();
        _docContent=cleanup_cnPage(_docContent);

        string page = "<doc>\n<docid>" + std::to_string(_docId) +        
                        "</docid>\n<title>" + _docTitle+
                        "</title>\n<url>" +_docUrl + 
                        "</url>\n<content>" + _docContent +                                                  
                        "</content>\n</doc>"+"\n";
        
        //due redunctant
        
        size_t topN = 5;
        uint64_t u64 = 0; // 将来去存储指纹的
        simhasher.make(page, topN, u64); // 算指纹

        cout<<u64<<"\n";

        bool saveFlag=true;

        if(vecOfHash.size()==0){
            vecOfHash.push_back(u64);
            _doc.append(page);

            umap[_docId]={pos,page.size()};
            pos+=page.size();

            child=child->NextSiblingElement();
            ++_docId;       
        }else{
            for(auto &ele:vecOfHash){
                if(Simhasher::isEqual(ele, u64)){
                    saveFlag=false;
                    child=child->NextSiblingElement();
                    break;
                }
            }

            if(saveFlag){
                vecOfHash.push_back(u64);

                _doc.append(page);

                umap[_docId]={pos,page.size()};
                pos+=page.size();

                child=child->NextSiblingElement();
                ++_docId;
            }
            
        }
               
    }

}

int WebPage::getDocId(){
    return _docId;
}

std::string WebPage::getDoc(){
    return _doc;
}