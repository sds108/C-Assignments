#ifndef T1_H_
#define T1_H_

typedef struct Edge Edge;
typedef struct Node Node;
typedef struct Stack Stack;
typedef struct Queue Queue;
typedef struct Graph Graph;

struct Edge {
	Edge* next;
	Edge* previous;
	Node* to;
};

struct Node {
	// Identifier & Visited Bool
	int number;
	int visited;
	
	// Adjacency list head & tail
	Edge* head;
	Edge* tail;
};

struct Stack {
	Stack* next;
	Node* node;
};

struct Queue {
	Queue* next;
	Queue* previous;
	Node* node;
};

struct Graph {
    // Number of Nodes
	int num_nodes;
	
	// Array of Node pointers, malloced to the size of num_nodes
	Node* array;
};

Graph* create_graph (int num_nodes); // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge (Graph *g, int from, int to); // adds a directed edge
void bfs (Graph* g, int origin); //implements breath first search and prints the results
void dfs (Graph* g, int origin); //implements depth first search and prints the results
void delete_graph (Graph* g); // delete the graph and all its data structures

#endif