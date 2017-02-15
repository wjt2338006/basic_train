#ifndef DATA_DISPLAY_H
#define DATA_DISPLAY_H
#include "data_struct.h"
#include <iostream>
#include <winsock2.h>
#include <map>
using namespace std;
class ip_display
{
public:
	
	 static  map<int, string> precedence_type;	//���ȼ���Ӧ
	 static  map<int, string> service_type;		//�������Ͷ�Ӧ
	 static map<int, string> protocol_type;		//Э�����Ͷ�Ӧ
	 
	//���캯��
	ip_display(ip_header * header)
	{
		//�汾��
		version = header->headerLen_ipVersion>>4;//�汾��ǰ����ֽڣ������ƶ�����uint��ȡ��
		
		//ͷ����
		headLen = (header->headerLen_ipVersion & 0x0f) * 4;//ͷ�����ȵ�λ�Ǻ����ֽڣ����4*15 = 60�ֽ�

		//��������
		//precedence = (int)header->tos >> 5;					
		//typeService = (int)(header->tos >> 1) & 0x0f;		
		typeService = header->tos;		//��������


		//�ܳ���
		totalLen = header->total_len;

		//identity
		identity = header->ident;

		//��־λ
		DF = (int)(header->flag_and_off >> 14) & 0x01;//�ƶ�14λ�����ұ�  ��ʾ����Ƭ
		MF = (int)(header->flag_and_off >> 13) & 0x01;//����Ƭʱ����Ƭ�����һ�Σ����һ���ֶε�ip����λ��Ϊ1

		unsigned short offset_tmp = header->flag_and_off & 0x1fff;//13λƬƫ�ƣ���ʾ��Ƭλ��
		offset = offset_tmp;

		//����ʱ��
		life = (int)header->ttl;

		//Э���ֶ�
		protocol = (int)header->proto;

		//ͷ��У���
		checkSum = checkSum;
		
		
		//ԭ��ַ
		ipSrc = string(inet_ntoa(*(in_addr*)&header->sourceIP));
			
		//Ŀ�ĵ�ַ
		ipDst = string(inet_ntoa(*(in_addr*)&header->destIP));

		source = *header;

	}
	//������������
	friend std::ostream& operator << (std::ostream &os, ip_display &ip)
	{
		os << "Version:" << protocol_type[ip.version] << "|Header Length:" << ip.headLen << "|Type of Service��" <<service_type[ip.typeService]
		   << "|Total Length:" << ip.totalLen << endl;

		os << "Identity:" << ip.identity << "|Flag:" << ip.DF << " " << ip.MF << "|Offset:" << ip.offset << endl;

		os << "TTL:" << ip.life << "|Protocol:" << protocol_type[ip.protocol] << "|Header Check Sum:" << ip.checkSum << endl;

		os << "IP Src:" << ip.ipSrc << endl;

		os << "IP Dst:" << ip.ipDst << endl;
		return os;
	}

public:
	unsigned int version;
	unsigned short headLen;
	unsigned int precedence;
	unsigned int typeService;
	unsigned int  totalLen;

	unsigned short identity;
	int DF, MF;
	int offset;

	int life;
	int protocol;
	unsigned short checkSum;
	string ipSrc;
	string ipDst;

	ip_header source;
};

//������ͽṹͬip
class tcp_display
{
public:
	tcp_display(tcp_header *header, unsigned short tcp_len)
	{
		source = *header;
		src_port = ntohs(header->src_port);
		dst_port = ntohs(header->dst_port);
		len = header->len_reserve >> 4;

		unsigned  char  flag = header->flag;
		urg = flag & 0x01;			//ǰ����6λ�����������ǽ���ָ��
		ack = (flag & 0x02)>>1;		//ȷ�Ϻ��Ƿ���Ч����ȷ�ϱ��Ķ�
		psh = (flag & 0x04)>>2;		//Я�����ݣ����ն���Ҫȡ��
		rst = (flag & 0x08)>>3;		//���½������ӣ����ã���λ
		syn = (flag & 0x10)>>4;		//����������
		fin = (flag & 0x18)>>5;		//�ر�����
		
		
		//����ʵ��
		char *p_data;
		char *tcp_data_char = new char[tcp_len];
		memset(tcp_data_char, 0, sizeof(tcp_data_char));

		p_data = (char*)header;
		p_data += len;
		memcpy(tcp_data_char, p_data, tcp_len - len);
		data = tcp_data_char;
		delete[] tcp_data_char;
		

	}
	//������������
	friend std::ostream& operator << (std::ostream &os, tcp_display &tcp)
	{
		os << "src_port:" << tcp.src_port << "|dst_port:" << tcp.dst_port << endl
			<< "Seq:" << tcp.source.seq << endl
			<< "Ack:" << tcp.source.ack << endl
			<< "len:" << tcp.len << "|URG:" << tcp.urg << "|ACK:" << tcp.ack << "|PSH:" << tcp.psh << "|RST:" << tcp.rst << "|SYN:" << tcp.syn << "|FIN:" << tcp.fin << "|window:" << tcp.source.window << endl
			<< "checksum:" << tcp.source.check_sum << "|urp:" << tcp.source.urp << endl;
			//<< "data:" << endl << tcp.data << endl;
		return os;
	}
public:
	tcp_header source;
	unsigned short src_port;//16λԴ�˿�
	unsigned short dst_port;//16λĿ�Ķ˿�
	unsigned short len;
	unsigned short urg;
	unsigned short ack;
	unsigned short psh;
	unsigned short rst;
	unsigned short syn;
	unsigned short fin;
	string data;
};
class udp_display
{
public:
	udp_display(udp_header &header)
	{
		src_port = ntohs(header.src_port);
		dst_port = ntohs(header.dst_port);
		len = header.len;
		check_sum = header.check_sum;

	}
	friend std::ostream& operator << (std::ostream &os, udp_display &udp)
	{
		os << "src_port:" << udp.src_port << "|dst_port:" << udp.dst_port << endl
			<< "len" << udp.len <<"|checksum" << udp.check_sum<<endl;
		return os;
	}
public:
	unsigned short src_port;
	unsigned short dst_port;
	unsigned short len;			//UDP ����
	unsigned short check_sum;	//����

};

class icmp_display
{

};

#endif 
