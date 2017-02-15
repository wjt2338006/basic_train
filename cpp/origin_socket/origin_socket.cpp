#include "origin_socket.h"
#include <Mstcpip.h>
#include <WS2tcpip.h>
origin_socket::origin_socket(short inetLayType, short transLayType,short inetStructType)
	:Socket(inetLayType, transLayType,inetStructType)
{
	
};

//������װ�İ�
void origin_socket::bind(const char *ip)
{
	
	Socket::bind(ip, 0);	//���û���İ󶨣�ԭʼ�׽��ֲ���Ҫ�󶨣��������ﲻ�󶨻����
}

//ʹ�û���ģʽ�����Կ������������İ�
void origin_socket::useMixMode()
{
	DWORD lpvBuffer = 1;
	DWORD lpcbBytesReturned = 0;
	auto r = ioctlsocket(winSocket, SIO_RCVALL, &lpvBuffer);	//ʹ�û���ģʽ
	//auto r = WSAIoctl(winSocket, SIO_RCVALL, &lpvBuffer, sizeof(lpvBuffer), NULL, 0, &lpcbBytesReturned, NULL, NULL);  //winsock�����﷨
	if (r == -1)
	{
		cerr << GetLastError() << endl;
		throw runtime_error("use MixMode error");
	}
}

//set operate option on ip header  (can't use, in test)
//ʹ�û��׳�����ԭ����
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

//��ȡ�ṹ������һ�����Դ�ӡ�İ������ʽ
ip_display origin_socket::read_ip(char *pChar)
{	
	
	//ת���ɽṹ
	ip_header *ip;
	ip = (ip_header*)pChar;
	ip_display display(ip);
	
	return std::move(display);
}
