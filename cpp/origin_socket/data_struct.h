#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
class ip_header
{
public:
	unsigned char headerLen_ipVersion;		//4位首部长度，4位IP版本号
	unsigned char tos;							//8位服务类型TOS
	unsigned short total_len;					//16位总长度
	unsigned short ident;						//16位标示
	unsigned short flag_and_off;	//偏移量和3位标志位
	unsigned char ttl;				//8位生存时间TTL
	unsigned char proto;			//8位协议（TCP,UDP或其他）
	unsigned short checksum;		//16位IP首部检验和
	unsigned int sourceIP;			//32位源IP地址
	unsigned int destIP;			//32位目的IP地址
};
/*
class tcp_false_header
{
public:
	unsigned long src_addr;			//源地址
	unsigned long dst_addr;			//目的地址
	char mbz;						//0
	char  protocol_type;			//协议类型
	unsigned short tcp_len;			//TCP长度
};*/


class tcp_header
{
public:
	unsigned short src_port;//16位源端口
	unsigned short dst_port;//16位目的端口
	unsigned int seq;		//32位序列号
	unsigned int ack;		//32位确认号
	unsigned char len_reserve;	//4位首部长度/6位保留字
	unsigned char flag;			//6位标志位
	unsigned short window;		//16位窗口大小
	unsigned short check_sum;	//16位检验和
	unsigned short urp;		//16位紧急数据偏移量
};

class udp_header
{
public:
	unsigned short src_port;	//16位源端口
	unsigned short dst_port;	//16位目的端口
	unsigned short len;			//UDP 长度
	unsigned short check_sum;	//检查和
};


class icmp_header
{
public:
	unsigned short src_port;
	unsigned short dst_port;
	unsigned char type;	//类型	
	unsigned char code;	//代码
	unsigned short cksum;	//校验和
	unsigned short id;
	unsigned short seq;	//序列
	unsigned long timestamp;//时间戳
};



#endif