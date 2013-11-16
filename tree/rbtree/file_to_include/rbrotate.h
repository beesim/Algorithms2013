#ifndef _RBROTATE_H_
#define _RBROTATE_H_
#include<stdio.h>
#include<stdlib.h>
#include<rbtree.h>


#define bool int
#define RED 0
#define BLACK 1


int left_rotate(rb* T, node* x)
{
	node* y;
	y = x->right;
	x->right = y->left;
	if (y->left != &NIL) {
		y->left->p = x;
	}
	y->p = x->p;
	if (x->p == &NIL) {
		T->root = y;
	} else if (x == x->p->left) {
		x->p->left = y;
	} else {
		x->p->right = y;
	}
	y->left = x;
	x->p = y;
	return 0;
}



int right_rotate(rb* T, node* x)
{
	node* y;
	y = x->left;
	x->left = y->right;
	if (y->right != &NIL) {
		y->right->p = x;
	}
	y->p = x->p;
	if (x->p == &NIL) {
		T->root = y;
	} else if (x == x->p->left) {
		x->p->left = y;
	} else {
		x->p->right = y;
	}
	y->right = x;
	x->p = y;
	return 0;
}


#endif
