#include "../include/EchoServer.h"
#include "../include/EventLoop.h"
#include "../include/TcpConnection.h"

#include "../include/nlohmann/json.hpp"
#include "../include/SplitToolCppJieba.h"
#include "../include/Dictionary.h"
#include "../include/msgDuer.h"

#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <functional>

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
    // 处理业务逻辑
    Dictionary *pIns = Dictionary::getInstance();
    msgDuer msgduer(_msg,pIns);


    _con->sendInLoop(_msg);
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



