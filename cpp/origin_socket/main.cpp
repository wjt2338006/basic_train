#include <WinSock2.h>
#include <WS2tcpip.h>
#include "origin_socket.h"
void test_origin_socket();

//初始化几个映射类型
map<int, string> ip_display::service_type
{
	{ 0, "normal" },
	{ 1, "minimize monetary" }

};
map<int, string> ip_display::protocol_type
{
	{ 1, "ICMP" },
	{ 2, "IGMP" },
	{ 4, "IPV4" },
	{ 6, "TCP" },
	{ 17, "UDP" },
	{ 41, "IPV6" }

};
map<int, string> ip_display::precedence_type
{
	{ 0, "routine" },
	{ 1, "priority" },
	{ 2, "immediate" },
	{ 3, "flash" },
	{ 4, "flash ovveride" },
	{ 5, "ecp" },
	{ 6, "iwc" },
	{ 7, "network control" }

};


int main()
{
	//Socket::init();
	test_origin_socket();
}
void test_origin_socket()
{
	//请用管理员运行vs  xxxxxxxx
	origin_socket::init();		//1.初始化
	origin_socket o_socket;		//声明
	string ip = origin_socket::getIp("localhost");//2.获取本机地址
	
	
	o_socket.bind(ip.c_str());	//3.绑定ip地址到socket，（可选）
	o_socket.useMixMode();	//4.使用混杂模式 在0.0.0.0的情况下会出错，绑定一个特定地址没有问题
	while (true)
	{
		//以char的形式读取原始套接字里面的数据
		unique_ptr<char[]>   s_ptr = o_socket.readChar(65535);//5.读取
		char* pChar = s_ptr.get();
		//xxxxxxxxxxxxxxxxxxxxxx


		//将其作为ip结构解析 6.解析
		auto ip_display = o_socket.read_ip(pChar);
		cout << ip_display << endl;

		//再解析第四层
		//tcp
		if (ip_display.protocol == 6)
		{
			//这里需要tcp总长度，方便解析出tcp实体
			tcp_header *tcp_p = (tcp_header*)(pChar + ip_display.headLen);
			tcp_display tcp(tcp_p,ip_display.totalLen-ip_display.headLen);
			cout << tcp << endl;

		}
		//udp
		if (ip_display.protocol == 17)
		{
			udp_header *udp_p = (udp_header*)(pChar + ip_display.headLen);
			udp_display udp(*udp_p);
			cout << udp << endl;

		}
	}
	
	return;

} 