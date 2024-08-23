#include "../include/EchoServer.h"
#include "../include/EventLoop.h"
#include "../include/TcpConnection.h"

#include "../include/Dictionary.h"
#include "../include/msgDealer.h"
#include "../include/dealJson.h"
#include "../include/ProtocolParser.h"

#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <functional>

#define QUERY 1
#define SEARCH 2

using std::bind;
using std::cout;
using std::endl;
using std::map;
using std::set;
using std::string;
using std::vector;

MyTask::MyTask(const string &msg, const TcpConnectionPtr &con)
: _msg(msg), _con(con)
{
}
void MyTask::process()
{
    // deal with service
    // 1.first judge which service
    cout<<_msg<<"\n";
    cout<<_msg.size()<<"\n";
    
    ProtocolParser protocolparser(_msg);
    int whichService=protocolparser.judgeService();

    if(whichService==QUERY){
        Dictionary *pIns = Dictionary::getInstance();
        msgDealer msgdealer(_msg,pIns);
        vector<string> rws=msgdealer.getRecommandWords();

        /*test no prob*/
        // for(auto &ele:rws){
        //     cout<<ele<<" ";
        // }
        // cout<<"\n";

        dealJson dealjson(rws);
        string return_msg=dealjson.returnmsgBuilder();

        _con->sendInLoop(return_msg);

    }else if(whichService==SEARCH){

        _con->sendInLoop(_msg);
    }else{
        _con->sendInLoop("error type\n");
    }
    
}

EchoServer::EchoServer(size_t threadNum, size_t queSize, const string &ip, unsigned short port)
    : _pool(threadNum, queSize), _server(ip, port)
{
}

EchoServer::~EchoServer()
{
}

// 服务器的启动与停止
void EchoServer::start(){
    _pool.start();

    // 注册所有的回调
    using namespace std::placeholders;
    _server.setAllCallback(std::bind(&EchoServer::onNewConnection, this, _1), std::bind(&EchoServer::onMessage, this, _1), std::bind(&EchoServer::onClose, this, _1));

    _server.start();
}

void EchoServer::stop(){
    _pool.stop();
    _server.stop();
}

void EchoServer::onNewConnection(const TcpConnectionPtr &con){
    cout << con->toString() << " has connected!!!" << endl;
}

void EchoServer::onMessage(const TcpConnectionPtr &con){
    // 接收客户端的数据
    // cout<<"in EchoServer::onMessage\n";//no pro
    string msg = con->receive(); // here problem find
    cout << ">>recv msg from client: " << msg << endl;

    MyTask task(msg, con);

    _pool.addTask(std::bind(&MyTask::process, task));
}

void EchoServer::onClose(const TcpConnectionPtr &con){
    cout << con->toString() << " has closed!!!" << endl;
}



