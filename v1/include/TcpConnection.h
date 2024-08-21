#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "Socket.h"
#include "SocketIO.h"
#include "InetAddress.h"

#include <memory>
#include <functional>

using std::shared_ptr;
using std::function;

class EventLoop;

class TcpConnection
: public std::enable_shared_from_this<TcpConnection>
{
    using TcpConnectionPtr = shared_ptr<TcpConnection>;
    using TcpConnectionCallback = function<void(const TcpConnectionPtr &)>;
public:
    explicit TcpConnection(int fd, EventLoop *loop);
    ~TcpConnection();
    void send(const string &msg);
    void sendInLoop(const string &msg);
    string receive();
    //查看连接是否断开
    bool isClosed() const;

    //为了方便调试的函数
    string toString();

public:
    //添加三个回调的注册
    void setNewConnectionCallback(const TcpConnectionCallback &cb);
    void setMessageCallback(const TcpConnectionCallback &cb);
    void setCloseCallback(const TcpConnectionCallback &cb);
    
    //添加三个回调的执行
    void handleNewConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();
private:
    //获取本端地址与对端地址
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();

private:
    EventLoop *_loop;//让TcpConnection知道EventLoop的存在
    SocketIO _sockIO;

    //为了调试而加入的三个数据成员
    Socket _sock;
    InetAddress _localAddr;
    InetAddress _peerAddr;

    TcpConnectionCallback _onNewConnection;//连接建立
    TcpConnectionCallback _onMessage;//消息到达（文件描述符可读）
    TcpConnectionCallback _onClose;//连接断开
};

#endif
