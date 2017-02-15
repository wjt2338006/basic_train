//
// Created by RagPanda on 2016/4/6.
//

#include "Socket.h"


#include <string>
#include <winsock2.h>
#include <map>
#include <exception>
#include <iostream>
#include <sys/types.h>
#include <ws2tcpip.h>


void  Socket::init()
{
    WSADATA wsaData;
    if(0!=WSAStartup(MAKEWORD(2,2),&wsaData))
    {
        throw  runtime_error("winsocket init error");
    };
}
void  Socket::clean()
{
    WSACleanup();
}
Socket::Socket(short inetLayType, short transLayType)
{

    winSocketInetType = inetLayType;
    winSocketTransType = transLayType;
    winSocket= socket(inetLayType,transLayType,0);
    if(winSocket == INVALID_SOCKET)
    {
        throw  runtime_error("winsocket create error");
    }

}
Socket::Socket(short inetLayType, short transLayType,SOCKET clntSocket,SOCKADDR_IN socketAddr)
{
    winSocketInetType = inetLayType;
    winSocketTransType = transLayType;
    winSocket = clntSocket;
    winSocketAddr =socketAddr;
}


void Socket::bind(const char* ip,int port)
{
    onlyBindData(ip,port);

    if(::bind(winSocket,(SOCKADDR*) &winSocketAddr, sizeof(winSocketAddr)))
    {
        throw runtime_error("winsocket bind error");
    }

}
void Socket::bind(const char* ip,const char* port)
{
    bind(ip,atoi(port));
}


void Socket::listen(int max)
{
    if( SOCKET_ERROR == ::listen(winSocket,max))
    {
        throw runtime_error("winsocket listen error");
    }


}

Socket Socket::accept()
{
    SOCKADDR_IN clntAddr;
    SOCKET clntSocket;
    int szClntAddr;

    szClntAddr = sizeof(clntAddr);
    clntSocket = ::accept(winSocket,(SOCKADDR*)&clntAddr, &szClntAddr);
    if(INVALID_SOCKET == clntSocket)
    {
        throw runtime_error("winsocket accept error");
    }
    Socket clnt(winSocketInetType,winSocketTransType,clntSocket,clntAddr);
    return std::move(clnt);
}



void Socket::connect(const char *ip, int port)
{
    onlyBindData(ip,port);

    if(SOCKET_ERROR == ::connect(winSocket,(SOCKADDR*)&winSocketAddr, sizeof(winSocketAddr)) )
    {
        throw runtime_error("winsocket connect error");
    }
}

void Socket::connect(const char *ip,const char* port)
{
    connect(ip, atoi(port));
}



void Socket::onlyBindData(const char* ip, int port)
{
    memset(&winSocketAddr,0, sizeof(winSocketAddr));
    if(winSocketInetType == PF_INET)
    {
        winSocketAddr.sin_family = AF_INET;
    }
    winSocketAddr.sin_addr.s_addr = inet_addr(ip);
    winSocketAddr.sin_port = htons(port);
}



string Socket::read(size_t len)
{
    char* pChar = new char[len];
    unsigned  int i = 0;
    while(i < len)
    {
        pChar[i] = '\0';
        ++i;
    }

    int recvLength = 0;

    recvLength = recv(winSocket, pChar, len, 0);
    i=0;
    while( i< recvLength)
    {
        i++;
    }
    pChar[i] = '\0';


    string str(pChar);
    delete [] pChar;
    return std::move(str);
}

int Socket::write(string &writeData)//const char* writeData
{

    int writeLength = writeData.size();

    int result = 0;
    result = send(winSocket,writeData.c_str(),writeLength,0);
    if(result == SOCKET_ERROR)
    {
        throw runtime_error("winsocket send error");
    }
    return result;
}

/*
 * UDP function
 * */

//UDP无连接发送数据，需要ip和端口
size_t Socket::sendTo(string &sendData,const char *ip, const char *port)
{
    if(winSocketTransType != UDP)
    {
        throw runtime_error("winsocket send error:sendTo only use for UDP");
    }


    struct sockaddr_in sockAddr= convertAddr(ip,port);
    socklen_t  socketSize = sizeof(sockAddr );

    size_t  sendSize = sendto(winSocket,
                               sendData.c_str(),
                               sendData.length(),
                               0,
                               (struct sockaddr*)& sockAddr,
                               socketSize
    );
    if(sendSize == -1)
    {
        throw runtime_error("winsocket send error:sendTo fail");
    }
    return sendSize;

}
//获取原始地址
SOCKADDR_IN Socket::getWinSocketAddr()
{
    return winSocketAddr;
}

//UDP无连接接收，需要先绑定
string Socket::recvFrom(size_t len)
{
    if(winSocketTransType != Socket::UDP)
    {
        throw runtime_error("winsocket error:recvFrom only use for UDP");
    }
    char* pChar = new char[len];
    unsigned  int i = 0;
    while(i < len)
    {
        pChar[i] = '\0';
        ++i;
    }


    struct sockaddr_in sockAddr ;
    socklen_t  socketSize = sizeof(sockAddr);


    size_t  str_len = recvfrom(winSocket,pChar,len,0,
                                (struct sockaddr*)& sockAddr,
                                &socketSize);
    if(str_len  == -1)
    {
        throw runtime_error("winsocket error:call recvfrom fail");
    }
    if(str_len == 0)
    {
        delete [] pChar;
        return string();
    }

    string && returnString = string(pChar);
    delete [] pChar;
    return returnString;
}

//转换一个SOCKADDR_IN结构
SOCKADDR_IN Socket::convertAddr(const char *ip,const char* port)
{
    SOCKADDR_IN winSocketAddr;
    memset(&winSocketAddr,0, sizeof(winSocketAddr));
    if(winSocketInetType == PF_INET)
    {
        winSocketAddr.sin_family = AF_INET;
    }
    winSocketAddr.sin_addr.s_addr = inet_addr(ip);
    winSocketAddr.sin_port = htons(atoi(port));
    return winSocketAddr;
}

SOCKET Socket::getOriginSocket()
{
    return winSocket;
}
