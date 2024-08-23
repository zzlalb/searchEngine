#include "../include/SocketIO.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

SocketIO::SocketIO(int fd)
: _fd(fd)
{

}

SocketIO::~SocketIO()
{
    /* close(_fd); */
}

//len = 10000    1500/6     1000/1
int SocketIO::readn(char *buf, int len)
{
    int left = len;
    char *pstr = buf;
    int ret = 0;

    while(left > 0)
    {
        ret = read(_fd, pstr, left);
        if(-1 == ret && errno == EINTR)
        {
            continue;
        }
        else if(-1 == ret)
        {
            perror("read error -1");
            return -1;
        }
        else if(0 == ret)
        {
            break;
        }
        else
        {
            pstr += ret;
            left -= ret;
        }
    }

    return len - left;
}

int SocketIO::myread(char *buf, int len){
    int ret1=0,ret2=0;
    int num=0;
    ret1 = read(_fd, &num, sizeof(int));

    ret2=read(_fd,buf,num);

    return ret1+ret2;
}

int SocketIO::readLine(char *buf, int len)
{
    int left = len - 1;
    char *pstr = buf;
    int ret = 0, total = 0;

    while(left > 0)
    {
        //MSG_PEEK不会将缓冲区中的数据进行清空,只会进行拷贝操作
        //std::cout<<"here in SocketIO::readLine\n";
        ret = recv(_fd, pstr, left, MSG_PEEK);
        //std::cout<<"ret: "<<ret<<"\n";
        if(-1 == ret && errno == EINTR)
        {
            continue;
        }
        else if(-1 == ret)
        {
            perror("readLine error -1");
            return -1;
        }
        else if(0 == ret)
        {
            break;
        }
        else
        {
            for(int idx = 0; idx < ret; ++idx)
            {
                if(pstr[idx] == '\n')
                {
                    int sz = idx + 1;
                    readn(pstr, sz);
                    pstr += sz;
                    *pstr = '\0';//C风格字符串以'\0'结尾

                    return total + sz;
                }
            }

            readn(pstr, ret);//从内核态拷贝到用户态
            total += ret;
            pstr += ret;
            left -= ret;
        }

    }
    *pstr = '\0';

    return total - left;

}

int SocketIO::writen(const char *buf, int len)
{
    int left = len;
    const char *pstr = buf;
    int ret = 0;

    while(left > 0)
    {
        ret = write(_fd, pstr, left);
        if(-1 == ret && errno == EINTR)
        {
            continue;
        }
        else if(-1 == ret)
        {
            perror("writen error -1");
            return -1;
        }
        else if(0 == ret)
        {
            break;
        }
        else
        {
            pstr += ret;
            left -= ret;
        }
    }
    return len - left;
}
