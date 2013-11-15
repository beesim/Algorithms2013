#ifndef _RBTREE_H_
#define _RBTREE_H_
#include<stdio.h>
#include<stdlib.h>


#define bool int
#define RED 0
#define BLACK 1


typedef struct _node node;
struct _node{
	int key;
	node* left;
	node* right;
	node* p;
	bool color;
};

struct _node NIL = {0, &NIL, &NIL, &NIL, BLACK};


typedef struct _rb{
	node* root;
} rb;



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



int rb_insert_fixup(rb* T, node* z)
{
	node* y;
	while (z->p->color == RED) {
		printf("In!\n");
		/**/
		if (z->p == z->p->p->left) {
			y = z->p->p->right;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			} else if (z == z->p->right) {
				z = z->p;
				left_rotate(T, z);
			}
			z->p->color = BLACK;
			z->p->p->color = RED;
			right_rotate(T, z->p->p);
		}
		else {
			y = z->p->p->left;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			} else if (z == z->p->left) {
				z = z->p;
				right_rotate(T, z);
			}
			z->p->color = BLACK;
			z->p->p->color = RED;
			left_rotate(T, z->p->p);
		}
	}
	T->root->color = BLACK;
	return 0;
}




int rb_insert(rb* T, node* z)
{
//printf("@");
	node* y = &NIL;
	node* x = T->root;
	while (x != &NIL) {
		y = x;
		if (z->key < x->key) {
			x = x->left;
		} else {
			x = x-> right;
		}
	}

//printf("@");

	z->p = y;
	if (y == &NIL) {
		T->root = z;
	} else if (z->key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}
printf("@");

	z->left = &NIL;
	z->right = &NIL;
	z->color = RED;
	rb_insert_fixup(T, z);

	return 0;
}



int inorder_tree_walk(node* x)
{
	if (x == &NIL) return 0;
	inorder_tree_walk(x->left);
	printf(" %d ", x->key);
	inorder_tree_walk(x->right);
	return 0;
}


#endif
