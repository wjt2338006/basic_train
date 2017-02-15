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
	
	 static  map<int, string> precedence_type;	//优先级对应
	 static  map<int, string> service_type;		//服务类型对应
	 static map<int, string> protocol_type;		//协议类型对应
	 
	//构造函数
	ip_display(ip_header * header)
	{
		//版本号
		version = header->headerLen_ipVersion>>4;//版本号前半个字节，向右移动，用uint读取出
		
		//头长度
		headLen = (header->headerLen_ipVersion & 0x0f) * 4;//头部长度单位是后半个字节，最大4*15 = 60字节

		//服务类型
		//precedence = (int)header->tos >> 5;					
		//typeService = (int)(header->tos >> 1) & 0x0f;		
		typeService = header->tos;		//服务类型


		//总长度
		totalLen = header->total_len;

		//identity
		identity = header->ident;

		//标志位
		DF = (int)(header->flag_and_off >> 14) & 0x01;//移动14位到最右边  表示不分片
		MF = (int)(header->flag_and_off >> 13) & 0x01;//当分片时，分片的最后一段，最后一个分段的ip包此位设为1

		unsigned short offset_tmp = header->flag_and_off & 0x1fff;//13位片偏移，表示分片位置
		offset = offset_tmp;

		//生存时间
		life = (int)header->ttl;

		//协议字段
		protocol = (int)header->proto;

		//头部校验和
		checkSum = checkSum;
		
		
		//原地址
		ipSrc = string(inet_ntoa(*(in_addr*)&header->sourceIP));
			
		//目的地址
		ipDst = string(inet_ntoa(*(in_addr*)&header->destIP));

		source = *header;

	}
	//重载输出运算符
	friend std::ostream& operator << (std::ostream &os, ip_display &ip)
	{
		os << "Version:" << protocol_type[ip.version] << "|Header Length:" << ip.headLen << "|Type of Service：" <<service_type[ip.typeService]
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

//以下类和结构同ip
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
		urg = flag & 0x01;			//前面有6位保留，这里是紧急指针
		ack = (flag & 0x02)>>1;		//确认号是否有效，即确认报文段
		psh = (flag & 0x04)>>2;		//携带数据，接收端需要取走
		rst = (flag & 0x08)>>3;		//从新建立连接，重置，复位
		syn = (flag & 0x10)>>4;		//请求建立连接
		fin = (flag & 0x18)>>5;		//关闭连接
		
		
		//解析实体
		char *p_data;
		char *tcp_data_char = new char[tcp_len];
		memset(tcp_data_char, 0, sizeof(tcp_data_char));

		p_data = (char*)header;
		p_data += len;
		memcpy(tcp_data_char, p_data, tcp_len - len);
		data = tcp_data_char;
		delete[] tcp_data_char;
		

	}
	//重载输出运算符
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
	unsigned short src_port;//16位源端口
	unsigned short dst_port;//16位目的端口
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
	unsigned short len;			//UDP 长度
	unsigned short check_sum;	//检查和

};

class icmp_display
{

};

#endif 
