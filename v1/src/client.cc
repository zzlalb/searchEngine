#include <func.h>
#include <sys/select.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "../include/nlohmann/json.hpp"

using std::string;
using std::cout;

int main()
{
    //创建客户端套接字
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(clientfd, -1, "socket");
    printf("clientfd: %d\n", clientfd);

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));//初始化
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8888);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret = connect(clientfd, 
                      (const struct sockaddr *)&serveraddr, 
                      sizeof(serveraddr));
    ERROR_CHECK(ret, -1, "connect");

    printf("connect success\n");

    fd_set rdset;
    FD_ZERO(&rdset);
    char buff[65535] = {0};

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
            //从键盘获取的数据中包含一个'\n'(temporarily removed)

            //generate json object and use train protocol to send to server
            if(buff[0]=='q'){
                char tmp[10000] = {0};
                for(int i=0;i<strlen(buff)-2;++i){
                    tmp[i]=buff[i+1];
                }

                nlohmann::json json_object;

                json_object.push_back("query");
                json_object.push_back(tmp);

                int len=strlen(json_object.dump().c_str());

                //little train protocol
                memset(tmp,0,sizeof(tmp));
                strcpy(tmp,json_object.dump().c_str());

                cout<<tmp[strlen(tmp)-1]<<"\n";

                cout<<tmp<<"\n";
                ret = send(clientfd, &len, sizeof(len), 0);
                printf("first send %d bytes.\n", ret);
                ret = send(clientfd, tmp, len, 0);
                printf("second send %d bytes.\n", ret);

            }else if(buff[0]=='s'){
                char tmp[10000] = {0};
                for(int i=0;i<strlen(buff)-2;++i){
                    tmp[i]=buff[i+1];
                }

                nlohmann::json json_object;

                json_object.push_back("search");
                json_object.push_back(tmp);

                int len=strlen(json_object.dump().c_str());

                //little train protocol
                memset(tmp,0,sizeof(tmp));
                strcpy(tmp,json_object.dump().c_str());

                cout<<tmp[strlen(tmp)-1]<<"\n";

                cout<<tmp<<"\n";
                ret = send(clientfd, &len, sizeof(len), 0);
                printf("first send %d bytes.\n", ret);
                ret = send(clientfd, tmp, len, 0);
                printf("second send %d bytes.\n", ret);
            }
            
        }

        if(FD_ISSET(clientfd, &rdset)) {
            int ret=1;
            //while(ret!=0){
                memset(buff, 0, sizeof(buff));
                //从对端获取数据
                ret = recv(clientfd, buff, sizeof(buff), 0);
                if(ret == 0) {
                    //连接已经断开了
                     break;
                }

                nlohmann::json json_object = nlohmann::json::parse(buff);
                cout<<json_object[1].dump()<<"\n";
            //}
           
        }
    }
    printf("byebye.\n");

    close(clientfd);

    return 0;
}

