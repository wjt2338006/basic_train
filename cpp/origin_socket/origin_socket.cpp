#include "origin_socket.h"
#include <Mstcpip.h>
#include <WS2tcpip.h>
origin_socket::origin_socket(short inetLayType, short transLayType,short inetStructType)
	:Socket(inetLayType, transLayType,inetStructType)
{
	
};

//经过封装的绑定
void origin_socket::bind(const char *ip)
{
	
	Socket::bind(ip, 0);	//调用基类的绑定，原始套接字不需要绑定，但在这里不绑定会出错
}

//使用混杂模式，可以看到所有流过的包
void origin_socket::useMixMode()
{
	DWORD lpvBuffer = 1;
	DWORD lpcbBytesReturned = 0;
	auto r = ioctlsocket(winSocket, SIO_RCVALL, &lpvBuffer);	//使用混杂模式
	//auto r = WSAIoctl(winSocket, SIO_RCVALL, &lpvBuffer, sizeof(lpvBuffer), NULL, 0, &lpcbBytesReturned, NULL, NULL);  //winsock特有语法
	if (r == -1)
	{
		cerr << GetLastError() << endl;
		throw runtime_error("use MixMode error");
	}
}

//set operate option on ip header  (can't use, in test)
//使用会抛出错误，原因不明
void origin_socket::setOperateIp()
{
	bool flag = true;
	auto r = setsockopt(winSocket, IPPROTO_IP, IP_HDRINCL, (char*)&flag, sizeof(flag));
	if (r == -1)
	{
		cerr << GetLastError() << endl;
		throw runtime_error("can't operate ip struct");
	}
}

//读取结构，返回一个可以打印的包对象格式
ip_display origin_socket::read_ip(char *pChar)
{	
	
	//转换成结构
	ip_header *ip;
	ip = (ip_header*)pChar;
	ip_display display(ip);
	
	return std::move(display);
}
