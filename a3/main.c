#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main (int argc, char* argv[]) {
	printf("Creating Tree\n");
	Tree_Node* root = create_bst("FLOCCINAUCINIHILIPILIFICATION");
	
	printf("Searching\n");
	printf("%i\n", (int)tree_search(root, 'A'));
	printf("%i\n", (int)tree_search(root, 'B'));
	printf("%i\n", (int)tree_search(root, 'C'));
	printf("%i\n", (int)tree_search(root, 'D'));
	printf("%i\n", (int)tree_search(root, 'E'));
	printf("%i\n", (int)tree_search(root, 'F'));
	printf("%i\n", (int)tree_search(root, 'G'));
	printf("%i\n", (int)tree_search(root, 'H'));
	
	printf("Insert\n");
	tree_insert(&root, 'Z');
	
	printf("Printing\n");
	tree_print_sorted(root);
	
	printf("\nDeleting\n");
	tree_delete(root);
	
	return 0;
}