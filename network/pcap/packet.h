#ifndef _PACKET_H_
#define _PACKET_H_

#include<stdio.h>
#include<string.h>
#include<time.h>

#define TEST
//#define TEST_BITS
#define TEST_HEADER
#define TEST_PACKET
//#define OUTPUT

#define MAX 1024

struct pcap_file_header {
    unsigned int magic;
    unsigned short version_major;
    unsigned short version_minor;
    int thiszone;    
    unsigned int sigfigs;   
    unsigned int snaplen;   
    unsigned int linktype;  
};

struct pcap_pkthdr {
//    long  tv_sec;        
//    long  tv_usec;     
	int tv_sec;
	int tv_usec;
    unsigned int caplen;    
    unsigned int len;       
};

struct ll_hdr{
    char dst_mac[6];
    char src_mac[6];
    char type[2];
};

struct ip_hdr{
    int overload[2];
    char ttl;
    char protocol;
    unsigned short checksum;
    unsigned char src_ip[4];
    unsigned char dst_ip[4];
};

struct tcp_hdr{
    unsigned char src_port[2];
    unsigned char dst_port[2];
    //...
};


struct packet {
    struct pcap_pkthdr pp;
    struct ll_hdr lh;
    struct ip_hdr ih;
    struct tcp_hdr th;
    //...
	//char* content =  the bytes captured but left.
};


#ifdef OUTPUT
int output_time(long tv_sec, long tv_usec)
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

inline void output_ip(unsigned char* ip)
{
    printf("%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
}
#else
inline void output_time(long tv_sec, long tv_usec) {}
inline int output_mac(char* MAC) {}
inline int output_ip(unsigned char* ip) {}
#endif


#endif
