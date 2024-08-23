#ifndef __ECHOSERVER_H__
#define __ECHOSERVER_H__

#include "ThreadPool.h"
#include "TcpServer.h"

#include "getWebpageLibs.h"
#include "Dictionary.h"

class MyTask
{
public:
    MyTask(const string &msg, const TcpConnectionPtr &con,Dictionary* pInsdic,getWebpageLibs* pInswebpage);
    void process();

private:
    string _msg;
    TcpConnectionPtr _con;

    Dictionary* _pInsdic;
    getWebpageLibs* _pInswebpage;
};

class EchoServer
{
public:
    friend class MyTask;
public:
    EchoServer(size_t threadNum, size_t queSize
               , const string &ip
               , unsigned short port);
    ~EchoServer();

    //服务器的启动与停止
    void start();
    void stop();

    void onNewConnection(const TcpConnectionPtr &con);
    void onMessage(const TcpConnectionPtr &con);
    void onClose(const TcpConnectionPtr &con);

private:
    ThreadPool _pool;
    TcpServer _server;
    Dictionary* _pInsdic;
    getWebpageLibs* _pInswebpage;

};

#endif
