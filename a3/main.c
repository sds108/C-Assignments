#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main (int argc, char* argv[]) {
	printf("Input String : \"FLOCCINAUCINIHILIPILIFICATION\"\n");
	
	printf("\nCreating Tree\n");
	Tree_Node* root = create_bst("FLOCCINAUCINIHILIPILIFICATION");
	
	printf("\nSearching\n");
	if (tree_search(root, 'A') != NULL) printf("Found \'A\'\n");
	else printf("Did not find \'A\'\n");
	
	if (tree_search(root, 'B') != NULL) printf("Found \'B\'\n");
	else printf("Did not find \'B\'\n");
	
	if (tree_search(root, 'C') != NULL) printf("Found \'C\'\n");
	else printf("Did not find \'C\'\n");
	
	if (tree_search(root, 'D') != NULL) printf("Found \'D\'\n");
	else printf("Did not find \'D\'\n");
	
	if (tree_search(root, 'E') != NULL) printf("Found \'E\'\n");
	else printf("Did not find \'E\'\n");
	
	if (tree_search(root, 'F') != NULL) printf("Found \'F\'\n");
	else printf("Did not find \'F\'\n");
	
	if (tree_search(root, 'G') != NULL) printf("Found \'G\'\n");
	else printf("Did not find \'G\'\n");
	
	if (tree_search(root, 'H') != NULL) printf("Found \'H\'\n");
	else printf("Did not find \'H\'\n");
	
	printf("\nInserting \'Z\'\n");
	tree_insert(&root, 'Z');
	
	printf("\nPrinting the Tree\n");
	tree_print_sorted(root);
	
	printf("\n\nDeleting the Tree\n");
	tree_delete(root);
	
	return 0;
}