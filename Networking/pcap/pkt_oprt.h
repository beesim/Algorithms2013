#ifndef _PKT_OPRT_H_
#define _PKT_OPRT_H_

#include<stdio.h>
#include<string.h>
#include<time.h>
#include "packet.h"


int cmp_src_ip(const void* p1, const void* p2)
{
	return *(int*)(((packet*)p1)->ih.src_ip) - *(int*)(((packet*)p2)->ih.src_ip);
}
int cmp_dst_ip(const void* p1, const void* p2)
{
	return *(int*)(((packet*)p1)->ih.dst_ip) - *(int*)(((packet*)p2)->ih.dst_ip);
}
int cmp_src_port(const void* p1, const void* p2)
{
	return *(int*)(((packet*)p1)->th.src_port) - *(int*)(((packet*)p2)->th.src_port);
}
int cmp_dst_port(const void* p1, const void* p2)
{
	return *(int*)(((packet*)p1)->th.dst_port) - *(int*)(((packet*)p2)->th.dst_port);
}
int cmp_time(const void* p1, const void* p2)
{
	if (((packet*)p1)->pp.tv_sec - ((packet*)p2)->pp.tv_sec == 0) {
		return ((packet*)p1)->pp.tv_usec - ((packet*)p2)->pp.tv_usec;
	}
	return ((packet*)p1)->pp.tv_sec - ((packet*)p2)->pp.tv_sec;
}



#endif
