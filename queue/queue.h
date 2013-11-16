#ifndef _QUEUE_H_
#define _QUEUE_H_
#include<stdio.h>

#define MAX 256

typedef struct {
	int key;
} item;

item* Q[MAX];
/*
 * head : the element to remove
 * tail: the element position to add
 * head == tail: the queue is empty
 * head = tail + 1: the queue is full
 */
int head = 0, tail = 0;

int enqueue(item *x) 
{
	if (head == tail + 1) {
//		perror("Queue full.\n");
		return -1;
	}
	Q[tail] = x;
	tail = (tail + 1) % MAX;
	return 0;
}

int dequeue(item** x)
{
	if (head == tail) {
//		perror("Queue empty.\n");
		return -1;
	}
	*x = Q[head];
	head = (head + 1) % MAX;
	return 0;
}

#endif
