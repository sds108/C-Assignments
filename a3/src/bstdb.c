#include "bstdb.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#define MAX_STRING_LENGTH 50

// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.

typedef struct Tree_Node Tree_Node;
struct Tree_Node {
	int id;
	char name[MAX_STRING_LENGTH];
	int word_count;
	char author[MAX_STRING_LENGTH];
	Tree_Node* higher;
	Tree_Node* lower;
};

// Your Maximum BST Size, Count, and other Variables
int midpoint;
int limit;
int node_counter = 0;
int node_multiplier = 0;
int level = 0;
int level_counter = 0;
Tree_Node* root = NULL;

long double comparisions = 0;
long double search_nodes = 0;
long double searches = 0;
unsigned long long duplicates = 0;
int two_to_level = 1;

int balanced_nodes = 0;
int unbalanced_nodes = 0;
int leaves = 0;

int log_result = 0;

void find_max_power () {
	unsigned int temp = UINT_MAX / 2;
	log_result = round(log2(temp)) - 2;
	
	limit = pow(2, log_result);
}
	

int int_pow (int base, int power) {
	int sum = 1;
	
	if (power > 0) {
		while (power > 0) {
			sum *= base;
			power--;
		}
	} else if (power < 0) {
		while (power < 0) {
			sum /= base;
			power++;
		}
	}
	
	return sum;
}

void update_multipliers () {
	if (level_counter > two_to_level - 1) {
		level++;
		two_to_level = pow(2, level);
		level_counter = -(two_to_level - 1);
	}
}

Tree_Node* create_node (int id, char *name, int word_count, char *author) {
	Tree_Node* node = (Tree_Node*)malloc(sizeof(Tree_Node));
	node->id = id;
	if (name != NULL) strcpy(node->name, name);
	node->word_count = word_count;
	if (author != NULL) strcpy(node->author, author);
	node->higher = NULL;
	node->lower = NULL;
	node_counter++;
	level_counter += 2;
	update_multipliers();
	return node;
}

Tree_Node* tree_insert_recursive (Tree_Node* current, int id) {
	// Loop until found an appropriate parent, or return null if found duplicate
	if (current->id > id) {
		if (current->lower != NULL) return tree_insert_recursive(current->lower, id);
		else return current;
	} else if (current->id < id) {
		if (current->higher != NULL) return tree_insert_recursive(current->higher, id);
		else return current;
	} else {
		printf("Duplicate of %i found\n", id);
		duplicates++;
		return NULL;
	}
}

// Return 1 if added, else 0
int tree_insert (int id, char *name, int word_count, char *author) {
	Tree_Node* parent = NULL;
	
    // Create Root if root doesn't exist
	if (root == NULL) root = create_node(id, name, word_count, author);
	else {
		parent = tree_insert_recursive(root, id);
		if (parent != NULL) {
			if (parent->id > id && parent->lower == NULL) parent->lower = create_node(id, name, word_count, author);
			else if (parent->id < id && parent->higher == NULL) parent->higher = create_node(id, name, word_count, author);
			else return 0;
		} else return 0;
	}
	
	return 1;
}


int bstdb_init (void) {
	// This function will run once (and only once) when the database first
	// starts. Use it to allocate any memory you want to use or initialize 
	// some globals if you need to. Function should return 1 if initialization
	// was successful and 0 if something went wrong.
	
	midpoint = INT_MIN / 2;
	midpoint = (-midpoint) - 1;
	find_max_power();
	
	return 1;
}

int bstdb_add (char *name, int word_count, char *author) {
	// This function should create a new node in the binary search tree, 
	// populate it with the name, word_count and author of the arguments and store
	// the result in the tree.
	//
	// This function should also generate and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	// How you generate this ID is up to you, but it must be an integer. Note
	// that this ID should also form the keys of the nodes in your BST, so
	// try to generate them in a way that will result in a balanced tree.
	//
	// If something goes wrong and the data cannot be stored, this function
	// should return -1. Otherwise it should return the ID of the new node
	
	int id = midpoint + round(((long double)limit / two_to_level) * (long double)(level_counter));
	
	// Make sure you do not exceed the limit of items
	if (level > log_result) {
		printf("Maximum Reached\n");
		return -1;
	}
	
	// Else add node
	if (tree_insert(id, name, word_count, author)) return id;
	else {
		printf("add error\n");
		return -1;
	}
}

Tree_Node* tree_search_recursive (Tree_Node* current, int id) {
	// Loop until found node or null
	search_nodes++;
	if (current->id == id) {
		comparisions++;
		search_nodes--;
		return current;
	} else if (current->id > id) {
		comparisions += 3;
		if (current->lower != NULL) return tree_search_recursive(current->lower, id);
		else return NULL;
	} else if (current->id < id) {
		comparisions += 4;
		if (current->higher != NULL) return tree_search_recursive(current->higher, id);
		else return NULL;
	} else {
		comparisions += 3;
		printf("%i Not Found\n", id);
		return NULL;
	}
}

void DFS_inOrder (Tree_Node* current) {
	if (current == NULL) return;
	
	DFS_inOrder(current->lower);
	printf("ID: %-20iName: %-30sAuthor: %-20sWord Count: %i\n", current->id, current->name, current->author, current->word_count);
	DFS_inOrder(current->higher);
}

void DFS_Delete (Tree_Node* current) {
	if (current == NULL) return;
	
	DFS_Delete(current->lower);
	DFS_Delete(current->higher);
	
	free(current);
}

int bstdb_get_word_count (int id) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1
	Tree_Node* result = tree_search_recursive(root, id);
	searches++;
	comparisions++;
	if (result != NULL) return result->word_count;
	else return -1;
}

char* bstdb_get_name (int id) {
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0
	Tree_Node* result = tree_search_recursive(root, id);
	searches++;
	comparisions++;
	if (result != NULL) return result->name;
	else return 0;
}

// Check for unbalanced nodes
void DFS_Balanced_Test (Tree_Node* current) {
	if (current == NULL) return;
	
	if (current->lower != NULL && current->higher != NULL) balanced_nodes++;
	else if (current->lower == NULL && current->higher == NULL) leaves++;
	else if (current->lower == NULL || current->higher == NULL) unbalanced_nodes++;
	
	DFS_Balanced_Test(current->lower);
	DFS_Balanced_Test(current->higher);
}

void DFS_Duplicate_Test (Tree_Node* current) {
	if (current == NULL) return;
	tree_search_recursive(root, current->id);
	DFS_Duplicate_Test(current->lower);
	DFS_Duplicate_Test(current->higher);
}

int factorial (int n) {
	int sum = 1;
	while (n > 0) {
		sum *= n;
		n--;
	}
	return sum;
}

int sum_of_powers (int base, int highest_power) {
	int sum = 0;
	
	while (highest_power >= 0) {
		sum += int_pow(base, highest_power);
		highest_power--;
	}
	
	return sum;
}

void bstdb_stat (void) {
	// Use this function to show off! It will be called once after the 
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result? 
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?
	
	printf("STAT\n");
	
	DFS_Balanced_Test(root);
	
	printf("%-28s-> %d\n", "Balanced Nodes", balanced_nodes);
	
	printf("%-28s-> %d\n", "Unbalanced Nodes", unbalanced_nodes);
	
	printf("%-28s-> %d\n", "Leaves (End Nodes)", leaves);
	
	printf("%-28s-> %d\n", "Total Nodes", balanced_nodes + leaves + unbalanced_nodes);
	
	printf("%-28s-> ", "List size matches expected?");
	if ((balanced_nodes + leaves + unbalanced_nodes) == node_counter) printf("Y\n");
	else printf("N\n");
	
	printf("%-28s-> %Lf\n", "Avg comparisons per search", comparisions / searches);
	
	printf("%-28s-> %Lf\n", "Avg traversals per search", search_nodes / searches);
	
	printf("%-28s-> ", "Duplicates");
	DFS_Duplicate_Test(root);
	printf("%llu\n", duplicates);
	
	// Describing Method
	printf("\n\nMETHOD\nIn order to balance the Tree, \nthe IDs are evenly dispersed over a large range of numbers.");
	printf("\nBy using the limits.h library, \nwe are able to find the maximum int value for our compiler.");
	printf("\nIf we take this number, divide it by two, we can make this our root id.");
	printf("\nFor a signed int, the middle number is 0, and appropriately so.");
	printf("\nHowever, it seems that the testing program for this Assignment, \nspecifically does not accept negative ID numbers,");
	printf("\nand counts them as insert errors.");
	printf("\nIt also does not allow for the changing of function return types, \nand therefore we cannot change the type of bstdb_add() to unsigned int.");
	printf("\nIn fact, if we wanted to maximise the range for this problem, \nwe would use a Long Long or unsigned Long Long instead of an int.");
	printf("\nHence, the range is actually cut in half or less due to our limitations.");
	printf("\nTherefore, our middle number, \nwhich is used as the ID for the root node is %i in this case.", midpoint);
	printf("\nI chose to use a smaller range to ensure we do not go out of bounds.");
	printf("\nWe can go %i left and right of this middle number.", limit);
	printf("\nSo our total range is from %i to %i (non-inclusive), \nwhich is a total of %i unique possible IDs.", midpoint - limit, midpoint + limit, 2*limit - 2);
	printf("\nIDs are distributed evenly, first at the middle point (the root), \nthen at 1/4 of the range and 3/4 of the range.");
	printf("\nThen 1/8, 3/8, 5/8, 7/8, then 1/16, 3/16, and so on, \nfor as many levels as necessary, unless the full range is filled,");
	printf("\nat which point the program refuses to add any more nodes.");
	printf("\nNotice how this implies that the range has to be some 2^n, \nin this case it is 2^%i.", log_result);
	printf("\nThis method ensures a perfectly balanced Binary Search Tree, \nwithout any duplicate IDs.");
	printf("\nThe only time we can find an unbalanced node using this method is, \nif we have an even number of nodes, this is as we have only one root.");
	printf("\n\nAs for checking for duplicates, there are multiple ways to do this. \nThis specific code goes through every single node in the tree,");
	printf("\nand searches for duplicates of that node in the whole tree.");
	printf("\nYou could also compare every single node to every other node in the tree, \nbut this takes incredible amounts of time to perform.");
	printf("\nIt is also important to mention that the way that nodes are inserted, \nin this program specifically, duplicates are rejected,");
	printf("\nand the program lets the user if a duplicate of a specific ID was found.\n\n");
}

void bstdb_quit (void) {
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
	DFS_Delete(root);
}
