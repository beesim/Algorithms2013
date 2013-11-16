#ifndef _PKT_OSTREAM_H_
#define _PKT_OSTREAM_H_

#include<stdio.h>
#include<string.h>
#include<time.h>
#include "packet.h"


//#ifdef OUTPUT
int output_time(int tv_sec, int tv_usec)
{
	struct tm *ptr;
	time_t lt = tv_sec;
	char str[80];
	ptr=localtime(&lt);
	strftime(str,100,"%F %X",ptr);
	printf("%s", str);
	return 0;
}

inline void output_mac(char* MAC)
{
	printf("%x%x:", MAC[0]>>4&0xf, MAC[0]&0xf);
	printf("%x%x:", MAC[1]>>4&0xf, MAC[1]&0xf);
	printf("%x%x:", MAC[2]>>4&0xf, MAC[2]&0xf);
	printf("%x%x:", MAC[3]>>4&0xf, MAC[3]&0xf);
	printf("%x%x:", MAC[4]>>4&0xf, MAC[4]&0xf);
	printf("%x%x", MAC[5]>>4&0xf, MAC[5]&0xf);
}

inline void output_ip(const unsigned char* ip)
{
	printf("%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
}

void output_pkt(const struct ex_packet pkt)
{
	printf("%3d\t", pkt.No);
	output_time(pkt.pp.tv_sec, pkt.pp.tv_usec);
	printf(" %x", (pkt.ih.protocol & 0xff));
	if (pkt.ih.protocol == 0x06) {
		printf("    TCP");
	} else if (pkt.ih.protocol == 0x11) {
		printf("    UDP");
	} else {
		printf(" IP|Not");
	}
	printf("\t\t<");
	output_ip(pkt.ih.src_ip);
	printf(":%x%x ---> ", pkt.th.src_port[0], pkt.th.src_port[1]);
	output_ip(pkt.ih.dst_ip);
	printf(":%x%x", pkt.th.dst_port[0], pkt.th.dst_port[1]);
	printf(">");
	printf ("\n");
}

//#else
//inline void output_time(long tv_sec, long tv_usec) {}
//inline int output_mac(char* MAC) {}
//inline int output_ip(unsigned char* ip) {}
//#endif

#endif
