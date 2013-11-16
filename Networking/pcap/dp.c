#include<stdio.h>
#include<string.h>
#include<time.h>
#include "packet.h"

#define TEST
//#define TEST_BITS
#define TEST_HEADER
#define TEST_PACKET
#define OUTPUT

//#define filename "./test/packet.pcap"
#define filename "./test/packet1.pcap"

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

