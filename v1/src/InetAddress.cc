#include "../include/InetAddress.h"
#include <strings.h>

InetAddress::InetAddress(const string &ip, unsigned short port)
{
    ::bzero(&_addr, sizeof(struct sockaddr_in));
    _addr.sin_family = AF_INET;
    //shift + k
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());//host->network
}

InetAddress::InetAddress(const struct sockaddr_in &addr)
: _addr(addr)
{

}

InetAddress::~InetAddress()
{

}

string InetAddress::ip() const
{
    //从网络字节序转换为本机字节序
    return string(inet_ntoa(_addr.sin_addr));
}

unsigned short InetAddress::port() const
{
    //从网络字节序转换为本机字节序
    return ntohs(_addr.sin_port);
}

const struct sockaddr_in *InetAddress::getInetAddrPtr() const
{
    return &_addr;
}
