//
// Created by RagPanda on 2016/4/6.
//

#ifndef NETWORK_SOCKET_H
#define NETWORK_SOCKET_H

#include <string>
#include <winsock2.h>
#include <map>
#include <exception>
#include <iostream>
#include <sys/types.h>
//#include <ws2tcpip.h>

using namespace std;
class Socket {
public:
    static const auto IPV4 = PF_INET;
    static const auto TCP = SOCK_STREAM;
    static const auto UDP = SOCK_DGRAM;

    static void init();

    static void clean();

    //构造函数
    Socket(short inetLayType, short transLayType);
    Socket(short inetLayType, short transLayType,SOCKET clntSocket,SOCKADDR_IN socketAddr);

    //绑定
    void bind(const char* ip,int port);
    void bind(const char* ip,const char* port);

    //监听
    void listen(int max);

    //TCP客户端接收
    Socket accept();



    void connect(const char *ip, int port);

    //连接
    void connect(const char *ip,const char* port);


    //只绑定数据不调用bind，供其它函数调用如connect,bind
    void onlyBindData(const char* ip, int port);



    //读取
    string read(size_t len = 1024);

    //写入
    int write(string &writeData);


    //获取原始地址
    SOCKADDR_IN getWinSocketAddr();
    //转换一个SOCKADDR_IN结构
    SOCKADDR_IN convertAddr(const char *ip,const char* port);
    //获取原始的套接字
    SOCKET getOriginSocket();

    //仅UDP使用
    //UDP无连接发送数据，需要ip和端口
    size_t sendTo(string &sendData,const char *ip, const char *port);

    //UDP无连接接收
    string recvFrom(size_t len);




private:
    SOCKET  winSocket;
    SOCKADDR_IN winSocketAddr;
    short winSocketInetType;
    short winSocketTransType;


};


#endif //NETWORK_SOCKET_H
