#include "../include/msgDuer.h"

using std::cout;
using std::pair;
using std::priority_queue;
using std::map;
using std::set;
using std::string;
using std::vector;

size_t nBytesCode(const char ch);
//2. 求取一个字符串的字符长度
std::size_t length(const std::string &str);
//3. 中英文通用的最小编辑距离算法
int editDistance(const std::string & lhs, const std::string &rhs);
vector<string> splitEnACn(const string &page);



msgDuer::msgDuer(string msg,Dictionary* pIns)
: _msg(msg)
, _pIns(pIns)
{}

void msgDuer::mergeSets(){
    vector<std::pair<string, int>> &dict = _pIns->getDict();
    map<string, set<int>> &index = _pIns->getIndex();

    vector<string> words;
    words = splitEnACn(_msg);

    for (auto &ele : words){
        cout << ele << "\n";
        for (auto &sets : index[ele]){
            _rwSet.insert(dict[sets]);
        }
    }
}

void msgDuer::buildComparer(){
    for(auto &ele:_rwSet){
        _dictComparer[ele.first]={editDistance(_msg,ele.first),ele.second};
    }
    /*test no prob*/
    // for(auto &ele:_dictComparer){
    //     cout<<"word: "<<ele.first<<"dis: "<<ele.second.first<<"fre "<<ele.second.second<<"\n";
    // }
}

// bool operator<(pair<string,pair<int,int>> &lhs,pair<string,pair<int,int>> &rhs){
//     if(lhs.second.first<rhs.second.first){
//         return false;
//     }else if(lhs.second.first==rhs.second.first){

//         if(lhs.second.second<rhs.second.second){
//             return false;
//         }else if(lhs.second.second==rhs.second.second){
//             return lhs.first.c_str()>rhs.first.c_str();
//         }else{
//             return true;
//         }      

//     }else{
//         return true;
//     }
// }

void msgDuer::fillPQueue(){
    for(auto &ele:_dictComparer){
        _pQueue.push({ele.first,{ele.second.first,ele.second.second}});
    }
}

vector<string> msgDuer::getRecommandWords(){
    mergeSets();
    buildComparer();
    fillPQueue();

    vector<string> words;
    int n=10;

    while(!_pQueue.empty()&&n>0){
        words.push_back(_pQueue.top().first);
        _pQueue.pop();
        --n;
    }

    return words;
}

size_t nBytesCode(const char ch){
    if (ch & (1 << 7)){
        int nBytes = 1;
        for (int idx = 0; idx != 6; ++idx){
            if (ch & (1 << (6 - idx))){
                ++nBytes;
            }else{
                break;
            }
        }
        return nBytes;
    }
    return 1;
}

vector<string> splitEnACn(const string &page){
    vector<string> ret;
    for (size_t i = 0; i < page.size();){
        string tmp;
        int len = nBytesCode(page[i]);
        if (len == 1){
            tmp = page[i];
            ret.push_back(tmp);
            ++i;
        }else{
            for (int j = 0; j < len; ++j){
                tmp.push_back(page[i + j]);
            }
            ret.push_back(tmp);
            i += len;
        }
    }
    return ret;
}

std::size_t length(const std::string &str){
    std::size_t ilen = 0;
    for (std::size_t idx = 0; idx != str.size(); ++idx){
        int nBytes = nBytesCode(str[idx]);
        idx += (nBytes - 1);
        ++ilen;
    }
    return ilen;
}

int triple_min(const int &a, const int &b, const int &c){
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

int editDistance(const std::string &lhs, const std::string &rhs){
    // 计算最小编辑距离-包括处理中英文
    size_t lhs_len = length(lhs);
    size_t rhs_len = length(rhs);
    int editDist[lhs_len + 1][rhs_len + 1];

    for (size_t idx = 0; idx <= lhs_len; ++idx){
        editDist[idx][0] = idx;
    }

    for (size_t idx = 0; idx <= rhs_len; ++idx){
        editDist[0][idx] = idx;
    }

    std::string sublhs, subrhs;
    for (std::size_t dist_i = 1, lhs_idx = 0; dist_i <= lhs_len; ++dist_i,++lhs_idx){
        size_t nBytes = nBytesCode(lhs[lhs_idx]);
        sublhs = lhs.substr(lhs_idx, nBytes);
        lhs_idx += (nBytes - 1);

        for (std::size_t dist_j = 1, rhs_idx = 0;dist_j <= rhs_len; ++dist_j, ++rhs_idx){
            nBytes = nBytesCode(rhs[rhs_idx]);
            subrhs = rhs.substr(rhs_idx, nBytes);
            rhs_idx += (nBytes - 1);

            if (sublhs == subrhs){
                editDist[dist_i][dist_j] = editDist[dist_i - 1][dist_j -1];
            }else{
                editDist[dist_i][dist_j] =
                    triple_min(editDist[dist_i][dist_j - 1] + 1,
                               editDist[dist_i - 1][dist_j] + 1,
                               editDist[dist_i - 1][dist_j - 1] + 1);
            }
        }
    }
    return editDist[lhs_len][rhs_len];
}