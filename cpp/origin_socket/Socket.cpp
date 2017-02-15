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
//根据一个域名，获取改域名ip
string Socket::getIp(const string &name)
{
	const char *p = name.c_str();
	hostent *host;		//声明地址结构指针
	host = gethostbyname(p);	//调用系统的根据域名获取ip的函数，返回一个地址结构
	char buff[256];			//定义一个缓存
	inet_ntop(host->h_addrtype, host->h_addr_list[0], buff, sizeof(buff));//将地址结构中的地址转换成char*的形式
	return string(buff);//将char* 转换成string 返回
	
}



//初始化Socket
Socket::Socket(short inetLayType, short transLayType,short inetStructType)
{
    winSocketInetType = inetLayType;
    winSocketTransType = transLayType;
	winSocket = socket(inetLayType, transLayType, inetStructType);
    if(winSocket == INVALID_SOCKET)
    {
		cout << GetLastError() << endl;;
        throw  runtime_error("winsocket create error");
    }

}

//专门负责接收accept地址的套接字
Socket::Socket(short inetLayType, short transLayType,SOCKET clntSocket,SOCKADDR_IN socketAddr)
{
    winSocketInetType = inetLayType;
    winSocketTransType = transLayType;
    winSocket = clntSocket;
    winSocketAddr =socketAddr;
}

//绑定
void Socket::bind(const char* ip,int port)
{
	//先绑定套接字地址数据
    onlyBindData(ip,port);
	//再告知系统绑定套接字（系统调用）
    if(::bind(winSocket,(SOCKADDR*) &winSocketAddr, sizeof(winSocketAddr)))
		//sockaddr是通用的地址结构，sockeaddr_in是internet的地址结构，都是16字节，在传入时可以强制转换
    {
        throw runtime_error("winsocket bind error");
    }

}
//绑定
void Socket::bind(const char* ip,const char* port)
{
    bind(ip,atoi(port));
}

//监听
void Socket::listen(int max)
{
    if( SOCKET_ERROR == ::listen(winSocket,max))
    {
        throw runtime_error("winsocket listen error");
    }


}

//接收
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


//连接，重载的int类型的
void Socket::connect(const char *ip, int port)
{
    onlyBindData(ip,port);

    if(SOCKET_ERROR == ::connect(winSocket,(SOCKADDR*)&winSocketAddr, sizeof(winSocketAddr)) )
    {
        throw runtime_error("winsocket connect error");
    }
}
//连接
void Socket::connect(const char *ip,const char* port)
{
    connect(ip, atoi(port));
}


//仅仅绑定数据，但是没有系统调用
void Socket::onlyBindData(const char* ip, int port)
{
    memset(&winSocketAddr,0, sizeof(winSocketAddr));	//初始化地址结构中的数据为0
    if(winSocketInetType == PF_INET)//设定地址类型
    {
        winSocketAddr.sin_family = AF_INET;
    }
    winSocketAddr.sin_addr.s_addr = inet_addr(ip);//转换地址字符串到大端
    winSocketAddr.sin_port = htons(port);//转换端口，int到大端
}


//读取
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
	if (recvLength == -1)
	{
		cerr << GetLastError() << endl;
		throw runtime_error("read error");
	}
    string str(pChar);
    delete [] pChar;
    return std::move(str);
}

unique_ptr<char[]>   Socket::readChar(size_t len)
{
	unique_ptr<char[]> pChar(new char[len]);//声明一个智能指针，分配内存

	//获取原始指针，并把其中所有字节设为\0,相当于memset函数的功能
	char *p = pChar.get();
	unsigned  int i = 0;
	while (i < len)
	{
		pChar[i] = '\0';
		++i;
	}

	//读取套接字中的数据
	int recvLength = recv(winSocket, p, len, 0);

	//错误处理
	if (recvLength == -1)
	{
		cerr << GetLastError() << endl;
		throw runtime_error("read error");
	}


	return pChar;

}
//写
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

	//初始化一个缓存区
    char* pChar = new char[len];
    unsigned  int i = 0;
    while(i < len)
    {
        pChar[i] = '\0';
        ++i;
    }

	//设置地址
    struct sockaddr_in sockAddr ;
    socklen_t  socketSize = sizeof(sockAddr);
    size_t  str_len = recvfrom(winSocket,pChar,len,0,
                                (struct sockaddr*)& sockAddr,
                                &socketSize);

	//把字符串初始化了
    if(str_len  == -1)
    {
        throw runtime_error("winsocket error:call recvfrom fail");
    }
    if(str_len == 0)
    {
        delete [] pChar;
        return string();
    }

	//分配string实例
    string && returnString = string(pChar);
    delete [] pChar;
    return returnString;
}

//转换一个SOCKADDR_IN结构，仅需要传入地址和端口
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

//获取底层的套接字
SOCKET Socket::getOriginSocket()
{
    return winSocket;
}
