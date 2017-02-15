#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
class ip_header
{
public:
	unsigned char headerLen_ipVersion;		//4λ�ײ����ȣ�4λIP�汾��
	unsigned char tos;							//8λ��������TOS
	unsigned short total_len;					//16λ�ܳ���
	unsigned short ident;						//16λ��ʾ
	unsigned short flag_and_off;	//ƫ������3λ��־λ
	unsigned char ttl;				//8λ����ʱ��TTL
	unsigned char proto;			//8λЭ�飨TCP,UDP��������
	unsigned short checksum;		//16λIP�ײ������
	unsigned int sourceIP;			//32λԴIP��ַ
	unsigned int destIP;			//32λĿ��IP��ַ
};
/*
class tcp_false_header
{
public:
	unsigned long src_addr;			//Դ��ַ
	unsigned long dst_addr;			//Ŀ�ĵ�ַ
	char mbz;						//0
	char  protocol_type;			//Э������
	unsigned short tcp_len;			//TCP����
};*/


class tcp_header
{
public:
	unsigned short src_port;//16λԴ�˿�
	unsigned short dst_port;//16λĿ�Ķ˿�
	unsigned int seq;		//32λ���к�
	unsigned int ack;		//32λȷ�Ϻ�
	unsigned char len_reserve;	//4λ�ײ�����/6λ������
	unsigned char flag;			//6λ��־λ
	unsigned short window;		//16λ���ڴ�С
	unsigned short check_sum;	//16λ�����
	unsigned short urp;		//16λ��������ƫ����
};

class udp_header
{
public:
	unsigned short src_port;	//16λԴ�˿�
	unsigned short dst_port;	//16λĿ�Ķ˿�
	unsigned short len;			//UDP ����
	unsigned short check_sum;	//����
};


class icmp_header
{
public:
	unsigned short src_port;
	unsigned short dst_port;
	unsigned char type;	//����	
	unsigned char code;	//����
	unsigned short cksum;	//У���
	unsigned short id;
	unsigned short seq;	//����
	unsigned long timestamp;//ʱ���
};



#endif