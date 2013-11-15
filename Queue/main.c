#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

item* makeitem(int i)
{
	item* p = (item*)malloc(sizeof(item));
	p->key = i;
	return p;
}


int main()
{
	int i;
	printf("Enqueueing:\n");
	scanf("%d", &i);
	while (i) {
		enqueue(makeitem(i));
		scanf("%d", &i);
	}
	printf("Dequeueing:\n");
	item* p;
	while((i = dequeue(&p)) != -1) {
		printf("%d -- ", p->key);
		free(p);
	}
	return 0;
}
