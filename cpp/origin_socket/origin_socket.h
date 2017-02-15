#ifndef ORIGIN_SOCKET_H
#define ORIGIN_SOCKET_H
#include "Socket.h"
#include "data_struct.h"
#include "data_display.h"
class origin_socket : public Socket
{
public:
	//����ԭʼ�׽�������
	static const auto ORIGIN_SOCKET = SOCK_RAW;
	//���캯��
	origin_socket(short inetLayType=origin_socket::IPV4,short transLayType=origin_socket::ORIGIN_SOCKET,short inetStructType = IPPROTO_IP);
	
	//ɾ�����������=
	origin_socket(const origin_socket&) = delete;
	origin_socket& operator=(const origin_socket&) = delete;
	
	//��һ��ip�����û�еĻ�ʹ��ȫ����
	void bind(const char *ip = nullptr);

	//��������ģʽ
	void useMixMode();

	//����Ϊ�Լ��ֶ�����ip����ǰ������
	void setOperateIp();

	//��ȡһ��ip������һ��ip�ṹ������ֱ�Ӵ�ӡ
	ip_display read_ip(char *pChar);
};
#endif