
#ifndef T3_H_
#define T3_H_

#define MAX_STRING_SIZE 50
typedef struct Node Node;
typedef struct Graph Graph;
typedef struct Stack Stack;

struct Node {
	// Matrix Components
	int visited;
	int permanent;
	int distance;
	int predecessor;
	
	// Linked list Component for when loading in
	Node* next;
	
	// Params
	int stopID;
	char name[MAX_STRING_SIZE];
	double latitude;
	double longitude;
};

struct Stack {
	Stack* next;
	int index;
};


struct Graph{
	int num_nodes;
	int** matrix;
	Node** array;
};

int load_edges (char *fname); //loads the edges from the CSV file of name fname
int load_vertices (char *fname);  //loads the vertices from the CSV file of name fname
void shortest_path(int startNode, int endNode); // prints the shortest path between startNode and endNode, if there is any
void free_memory (void); // frees any memory that was used

#endif