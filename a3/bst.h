#ifndef BST_H_
#define BST_H_

typedef struct Tree_Node Tree_Node;
struct Tree_Node {
	char data;
	int freq;
	Tree_Node* parent;
	Tree_Node* higher;
	Tree_Node* lower;
};


void tree_insert ( Tree_Node** root, char data );
Tree_Node* create_bst (char data[]);
Tree_Node* tree_search ( Tree_Node* root, char data );
void tree_print_sorted ( Tree_Node* root );
void tree_delete ( Tree_Node* root );


#endif