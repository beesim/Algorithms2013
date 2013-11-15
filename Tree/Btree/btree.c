#include <stdio.h>
#include <stdlib.h>
#include <cstring.h>

#define MAX	4


typedef struct _node {
	int n;
	struct _node* p;
	int key[MAX]
	struct _node* child[MAX + 1];
	bool leaf;
	/*
	 * 
	 */
} node;


typedef struct _btree {
	node* root;
} btree;


typedef _SchR {
	node* p;
	int index;
} SchR;


SchR* btree_search(node* T, int k)
{
	SchR* ret = (SchR*)malloc(sizeof(SchR));
	if (T == NULL) {
		return NULL;
	}
	int i = 0;
	while ((i < MAX) && (p->key[i] < k)) {
		i++;
	}
	if (p->key[i] == k) {
		ret->p = T;
		index = i;
		return ret;
	}
	if (T->leaf) {
		return NULL;
	}
	return btree_search(T->child[i], k);
}


int btree_insert(btree* T, node* p)
{

	return NULL;
}



















int main()
{
	return 0;
}
