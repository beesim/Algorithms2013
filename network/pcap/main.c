#include<stdio.h>
#include<string.h>
#include<time.h>
//#include<file.h>

#define MAX 1024

#define TEST
//#define TEST_BITS
#define TEST_HEADER
#define TEST_PACKET
//#define TEST_LL
//#define TEST_IP
//#define TEST_TCP

#define filename "./packet.pcap"
//#define filename "./packet1.pcap"


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
    long  tv_sec;        
    long  tv_usec;       
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
};


struct packet pkt[MAX];


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


inline int output_mac(char* MAC)
{
    printf("%x%x:", MAC[0]>>4&0xf, MAC[0]&0xf);
    printf("%x%x:", MAC[1]>>4&0xf, MAC[1]&0xf);
    printf("%x%x:", MAC[2]>>4&0xf, MAC[2]&0xf);
    printf("%x%x:", MAC[3]>>4&0xf, MAC[3]&0xf);
    printf("%x%x:", MAC[4]>>4&0xf, MAC[4]&0xf);
    printf("%x%x", MAC[5]>>4&0xf, MAC[5]&0xf);
}


inline int output_ip(unsigned char* ip)
{
    printf("%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
    return 0;
}


int main()
{
    #ifdef TEST_BITS
    printf("unsigned int: %d\n", sizeof(unsigned int));
    printf("unsigned short: %d\n", sizeof(unsigned short));
    printf("long: %d\n", sizeof(long));
    #endif

    FILE* pfile = NULL;
    if ((pfile = fopen(filename, "rb+")) == NULL) {
        printf("Fopen error.\n");
        return -1;
    }

    struct pcap_file_header pfh;
    fread(&pfh, sizeof(struct pcap_file_header), 1, pfile);
    #ifdef TEST_HEADER
    printf("magic\t\t: %x\n", pfh.magic);
    printf("version\t\t: %x:%x\n", pfh.version_major, pfh.version_minor);
    printf("thiszone\t: %x\n", pfh.thiszone);
    printf("sigfigs\t\t: %x\n", pfh.sigfigs);
    printf("snaplen\t\t: %x\n", pfh.snaplen);
    printf("linktype\t: %x\n", pfh.linktype);
    #endif 

    int offset = ftell(pfile);
    int itemnum = 1;
	int i = 0;
	printf ("HERE0!");
    while((fread(&pkt[i], sizeof(packet), 1, pfile)) != 0) {
	printf ("HERE1!");
        if ((pkt[i].lh.type[0] == 0x08) && (pkt[i].lh.type[1] == 0x00)) {
            printf("%3d\t", itemnum);
            output_time(pkt[i].pp.tv_sec, pkt[i].pp.tv_usec);
/*
            output_mac(pkt.lh.dst_mac);
            printf(" <-- ");
            output_mac(pkt.lh.src_mac);
*/
            printf(" %x", (pkt[i].ih.protocol & 0xff));
            if (pkt[i].ih.protocol == 0x06) {
                printf(" TCP");
            } else if (pkt[i].ih.protocol == 0x11) {
                printf(" UDP");
            } else {
                printf("  IP");
            }
            printf("\t\t<");
            output_ip(pkt[i].ih.src_ip);
            printf(":%x%x ---> ", pkt[i].th.src_port[0], pkt[i].th.src_port[1]);
            output_ip(pkt[i].ih.dst_ip);
            printf(":%x%x", pkt[i].th.dst_port[0], pkt[i].th.dst_port[1]);
            printf(">\n");
        }
        itemnum++;
		i++;
		if (i >= MAX) {
			break;
		}
        offset += sizeof(struct pcap_pkthdr) + pkt[i].pp.caplen;
        fseek(pfile, offset, SEEK_SET);
    }
	printf ("HERE2!");

    fclose(pfile);
    return 0;
}

