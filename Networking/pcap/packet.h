#ifndef _PACKET_H_
#define _PACKET_H_

#include<stdio.h>
#include<string.h>
#include<time.h>


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

struct ex_packet {
    struct pcap_pkthdr pp;
    struct ll_hdr lh;
    struct ip_hdr ih;
    struct tcp_hdr th;
	int No;	// from 0 - infinity
	int offset;
    //...
	//char* content =  the bytes captured but left.
};


#endif
