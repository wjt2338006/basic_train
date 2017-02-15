#include <WinSock2.h>
#include <WS2tcpip.h>
#include "origin_socket.h"
void test_origin_socket();

//��ʼ������ӳ������
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
	//���ù���Ա����vs  xxxxxxxx
	origin_socket::init();		//1.��ʼ��
	origin_socket o_socket;		//����
	string ip = origin_socket::getIp("localhost");//2.��ȡ������ַ
	
	
	o_socket.bind(ip.c_str());	//3.��ip��ַ��socket������ѡ��
	o_socket.useMixMode();	//4.ʹ�û���ģʽ ��0.0.0.0������»������һ���ض���ַû������
	while (true)
	{
		//��char����ʽ��ȡԭʼ�׽������������
		unique_ptr<char[]>   s_ptr = o_socket.readChar(65535);//5.��ȡ
		char* pChar = s_ptr.get();
		//xxxxxxxxxxxxxxxxxxxxxx


		//������Ϊip�ṹ���� 6.����
		auto ip_display = o_socket.read_ip(pChar);
		cout << ip_display << endl;

		//�ٽ������Ĳ�
		//tcp
		if (ip_display.protocol == 6)
		{
			//������Ҫtcp�ܳ��ȣ����������tcpʵ��
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