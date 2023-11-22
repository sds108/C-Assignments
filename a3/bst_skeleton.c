#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

#define MAX_STRING_LENGTH 10000

Tree_Node* create_node (Tree_Node* parent, char data) {
	Tree_Node* node = (Tree_Node*)malloc(sizeof(Tree_Node));
	
	node->data = data;
	node->freq = 1;
	node->parent = parent;
	node->higher = NULL;
	node->lower = NULL;
	
	return node;
}

Tree_Node* tree_insert_recursive (Tree_Node* current, char data) {
	// Loop until found an appropriate parent, or return null if found duplicate
	if (current->data == data) {
		current->freq++;
		return NULL;
	} else if (current->data > data) {
		if (current->lower != NULL) return tree_insert_recursive(current->lower, data);
		else return current;
	} else if (current->data < data) {
		if (current->higher != NULL) return tree_insert_recursive(current->higher, data);
		else return current;
	} else {
		printf("Error\n");
		return NULL;
	}
}

void tree_insert (Tree_Node** root, char data) {
	Tree_Node* parent = NULL;
	
    // Create Root if root doesn't exist
	if (*root == NULL) *root = create_node(NULL, data);
	else {
		parent = tree_insert_recursive(*root, data);
		if (parent != NULL) {
			if (parent->data > data && parent->lower == NULL) parent->lower = create_node(parent, data);
			else if (parent->data < data && parent->higher == NULL) parent->higher = create_node(parent, data);
			else printf("Error Insert\n");
		}
	}
}

Tree_Node* create_bst (char data[]){
    // Returns the pointer to Root
	int node = 0;
	char c = data[node];
	Tree_Node* root = NULL;
	
	while (c != '\0' && node < MAX_STRING_LENGTH) {
		tree_insert(&root, c);
		node++;
		c = data[node];
	}
	
	return root;
}

Tree_Node* tree_search_recursive (Tree_Node* current, char data) {
	// Loop until found node or null
	if (current->data == data) return current;
	else if (current->data > data) {
		if (current->lower != NULL) return tree_search_recursive(current->lower, data);
		else return NULL;
	} else if (current->data < data) {
		if (current->higher != NULL) return tree_search_recursive(current->higher, data);
		else return NULL;
	} else {
		printf("Not Found\n");
		return NULL;
	}
}

Tree_Node* tree_search (Tree_Node* root, char data) {
    // Recursive search
	return tree_search_recursive(root, data);
}

void DFS_inOrder (Tree_Node* current) {
	if (current == NULL) return;
	
	DFS_inOrder(current->lower);
	for (int i = 0; i < current->freq; i++) printf("%c", current->data);
	DFS_inOrder(current->higher);
}

void DFS_Delete (Tree_Node* current) {
	if (current == NULL) return;
	
	DFS_Delete(current->lower);
	DFS_Delete(current->higher);
	
	free(current);
}

void tree_print_sorted (Tree_Node* root) {	
	DFS_inOrder(root);
}

void tree_delete (Tree_Node* root) {
	DFS_Delete(root);
}