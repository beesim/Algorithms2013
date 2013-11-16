#include<stdio.h>
#include<string.h>
#include<time.h>
#include "packet.h"

#define TEST
//#define TEST_BITS
#define TEST_HEADER
#define TEST_PACKET
//#define OUTPUT

//#define filename "./packet.pcap"
#define filename "./packet1.pcap"

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


int main()
{
	struct packet pkt[MAX];

    FILE* pfile = NULL;
    if ((pfile = fopen(filename, "rb+")) == NULL) {
        printf("Fopen error.\n");
        return -1;
    }

    struct pcap_file_header pfh;
    fread(&pfh, sizeof(struct pcap_file_header), 1, pfile);

    int offset = ftell(pfile);
    int pktidx = 0;
    while((fread(&pkt[pktidx], sizeof(struct packet), 1, pfile)) != 0) {
#ifdef OUTPUT
        printf("%3d\t", pktidx);
        if ((pkt[pktidx].lh.type[0] == 0x08) && (pkt[pktidx].lh.type[1] == 0x00)) {
            output_time(pkt[pktidx].pp.tv_sec, pkt[pktidx].pp.tv_usec);
            printf(" %x", (pkt[pktidx].ih.protocol & 0xff));
            if (pkt[pktidx].ih.protocol == 0x06) {
                printf(" TCP");
            } else if (pkt[pktidx].ih.protocol == 0x11) {
                printf(" UDP");
            } else {
                printf("  IP");
            }
            printf("\t\t<");
            output_ip(pkt[pktidx].ih.src_ip);
            printf(":%x%x ---> ", pkt[pktidx].th.src_port[0], pkt[pktidx].th.src_port[1]);
            output_ip(pkt[pktidx].ih.dst_ip);
            printf(":%x%x", pkt[pktidx].th.dst_port[0], pkt[pktidx].th.dst_port[1]);
            printf(">");
        }
		printf ("\n");
#endif
        offset += sizeof(struct pcap_pkthdr) + pkt[pktidx].pp.caplen;
        pktidx++;
        fseek(pfile, offset, SEEK_SET);
    }

    fclose(pfile);
    return 0;
}

