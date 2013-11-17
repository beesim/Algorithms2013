#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "packet.h"
#include "pkt_ostream.h"
#include "pkt_oprt.h"

#define MAX 1024	// 1 M packet
#define ONCE 20480	// 1 K packet


#define TEST
//#define TEST_BITS
#define TEST_HEADER
#define TEST_PACKET
#define OUTPUT

//#define filename "./test/packet.pcap"
//#define filename "./test/packet1.pcap"
#define filename "./test/thunder_movie_yizuochengchi.pcap"

	

int main()
{
	struct ex_packet** P = (struct ex_packet**) malloc (MAX * sizeof (struct ex_packet*));
	int curpage = 0;
	P[curpage] = (struct ex_packet*) malloc (ONCE * sizeof (struct ex_packet));
	struct ex_packet* pkt = P[curpage];

    FILE* pfile = NULL;
    if ((pfile = fopen (filename, "rb+")) == NULL) {
        printf("Fopen error.\n");
        return -1;
    }

    struct pcap_file_header pfh;
    fread (&pfh, sizeof (struct pcap_file_header), 1, pfile);

    int offset = ftell (pfile);
    int pktidx = 0;
    while ((fread(&pkt[pktidx], sizeof (struct packet), 1, pfile)) != 0) {
		pkt[pktidx].No = pktidx;
		pkt[pktidx].offset = offset;
//		output_pkt (pkt[pktidx]);
        
		offset += sizeof (struct pcap_pkthdr) + pkt[pktidx].pp.caplen;
        pktidx++;
        fseek (pfile, offset, SEEK_SET);
		if (pktidx >= ONCE) {
			curpage++;
			P[curpage] = (struct ex_packet*) malloc (ONCE * sizeof (struct ex_packet));
			pkt = P[curpage];
		}
    }

	qsort(pkt, pktidx, sizeof (struct ex_packet), cmp_dst_ip);
	qsort(pkt, pktidx, sizeof (struct ex_packet), cmp_src_ip);
	qsort(pkt, pktidx, sizeof (struct ex_packet), cmp_time);
	int i;
	for (i = 0; i < pktidx; i++ ) {
		output_pkt (pkt[i]);
	}

    fclose (pfile);
	for (i = 0; i <= curpage; i++) {
		delete (P[i]);
	}
	delete (P);
    return 0;
}

