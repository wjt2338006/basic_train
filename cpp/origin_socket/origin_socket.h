#ifndef ORIGIN_SOCKET_H
#define ORIGIN_SOCKET_H
#include "Socket.h"
#include "data_struct.h"
#include "data_display.h"
class origin_socket : public Socket
{
public:
	//定义原始套接字类型
	static const auto ORIGIN_SOCKET = SOCK_RAW;
	//构造函数
	origin_socket(short inetLayType=origin_socket::IPV4,short transLayType=origin_socket::ORIGIN_SOCKET,short inetStructType = IPPROTO_IP);
	
	//删除拷贝构造和=
	origin_socket(const origin_socket&) = delete;
	origin_socket& operator=(const origin_socket&) = delete;
	
	//绑定一个ip，如果没有的话使用全网卡
	void bind(const char *ip = nullptr);

	//开启混杂模式
	void useMixMode();

	//设置为自己手动操作ip，不前不可用
	void setOperateIp();

	//读取一个ip，返回一个ip结构，可以直接打印
	ip_display read_ip(char *pChar);
};
#endif