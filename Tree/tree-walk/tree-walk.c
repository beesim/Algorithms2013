#include <stdio.h>

#typedef struct _node{
	struct _node* left_child;
	struct _node* right_child;
	int value;
} node;

(void) (tree_walk_func)(node* root);



void inorder(node* root)
{
	if (root == NULL) {
		return;
	}
	inorder(root->left_node);
	printf (" %d ", root->value);
	inorder(root->right_node);
	return;
}


void preorder(node* root)
{
	if (root == NULL) {
		return;
	}
	printf (" %d ", root->value);
	preorder(root->left_node);
	preorder(root->right_node);
	return;
}



void postorder(node* root)
{
	if (root == NULL) {
		return;
	}
	postorder(root->left_node);
	postorder(root->right_node);
	printf (" %d ", root->value);
	return;
}
