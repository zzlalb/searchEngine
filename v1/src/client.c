#include <func.h>
#include <sys/select.h>
#include <unistd.h>

//接收确定个字节的数据
int recvn(int sockfd, void * buff, int len)
{
    int left = len;
    char * pbuf = buff;
    int ret = 0;
    while(left > 0) {
        ret = recv(sockfd, pbuf, left, 0);
        if(ret < 0) {
            perror("recv");
            break;
        } else if (ret == 0) {
            break;
        }
        pbuf += ret;
        left -= ret;
    }
    return len - left;
}

int writen(int sockfd, const char *buf, int len)
{
    int left = len;
    const char *pstr = buf;
    int ret = 0;

    while(left > 0){
        ret = write(sockfd, pstr, left);
        if(-1 == ret && errno == EINTR){
            continue;
        }else if(-1 == ret){
            perror("writen error -1");
            return -1;
        }else if(0 == ret){
            break;
        }else{
            pstr += ret;
            left -= ret;
        }
    }
    return len - left;
}

int main()
{
    //创建客户端套接字
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(clientfd, -1, "socket");

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));//初始化
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8888);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret = connect(clientfd, 
                      (const struct sockaddr *)&serveraddr, 
                      sizeof(serveraddr));
    ERROR_CHECK(ret, -1, "connect");

    fd_set rdset;
    FD_ZERO(&rdset);
    char buff[1000] = {0};

    //对IO事件进行监听
    while(1) {
        FD_ZERO(&rdset);
        FD_SET(clientfd, &rdset);
        FD_SET(STDIN_FILENO, &rdset);

        select(clientfd + 1, &rdset, NULL, NULL, NULL);

        if(FD_ISSET(STDIN_FILENO, &rdset)) {
            //清空缓冲区
            memset(buff, 0, sizeof(buff));
            //从标准输入获取数据
            int ret = read(STDIN_FILENO, buff, sizeof(buff));
            if(ret == 0) {
                //按了ctrl + d   结束输入操作
                break;
            }
            printf("read ret: %d\n", ret);
            
            //发送给对端
            //从键盘获取的数据中包含一个'\n'
            ret = send(clientfd, buff, strlen(buff) - 1, 0);
            printf("send %d bytes.\n", ret);
        }

        if(FD_ISSET(clientfd, &rdset)) {
            //清空缓冲区
            memset(buff, 0, sizeof(buff));
            //从对端获取数据
            int ret = recv(clientfd, buff, sizeof(buff), 0);
            if(ret == 0) {
                //连接已经断开了
                break;
            }
            printf("recv msg: %s\n", buff);
        }
    }


    //先接收文件名
    char filename[100] = {0};
    int len = 0;
    ret = recvn(clientfd, (char*)&len, sizeof(len));//先接长度
    printf("ret: %d, filename's len:%d\n", ret, len);
    ret = recvn(clientfd, filename, len);//再接内容
    printf("ret: %d, recv msg:%s\n", ret, filename);
    
    int wfd = open(filename, O_CREAT | O_RDWR, 0644);
    ERROR_CHECK(wfd, -1, "open");

    //再获取的是文件长度
    off_t length = 0;
    recvn(clientfd, (char*)&length, sizeof(length));
    printf("file length: %ld\n", length);
    //最后接收文件内容
    char buff[1000] = {0};
    while(1) {
        ret = recvn(clientfd, (char*)&len, sizeof(len));//先接长度
        if(ret == 0) {
            break;
        }
        //可以确定接收len个字节的长度
        ret = recvn(clientfd, buff, len);//再接文件内容
        if(ret != 1000) {
            printf("ret: %d\n", ret);
        }
        //最后再写入本地
        write(wfd, buff, ret);
    }
    close(wfd);
    close(clientfd);

    return 0;
}

