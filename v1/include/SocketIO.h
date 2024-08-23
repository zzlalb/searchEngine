#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__

class SocketIO
{
public:
    explicit SocketIO(int fd);
    ~SocketIO();
    int myread(char *buf,int &num, int len);
    int readn(char *buf, int len);
    int readLine(char *buf, int len);
    int writen(const char *buf, int len);

private:
    int _fd;
};

#endif
