#include "t1.h"
#include <stdlib.h>
#include <stdio.h>

void unvisit_graph (Graph* g) {
	for (int i = 0; i < g->num_nodes; i++) {
		g->array[i].visited = 0;
	}
}

Stack* create_stack (Node* node) {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	
	stack->next = NULL;
	stack->node = node;
	
	return stack;
}

Queue* create_queue (Node* node) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	
	queue->next = NULL;
	queue->previous = NULL;
	queue->node = node;
	
	return queue;
}

// creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
Graph* create_graph (int num_nodes) {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	
	g->num_nodes = num_nodes;
	g->array = (Node*)malloc(num_nodes * sizeof(Node));
	
	for (int i = 0; i < num_nodes; i++) {
		g->array[i].number = i;
		g->array[i].visited = 0;
		g->array[i].head = NULL;
	}
	
	return g;
}

// adds a directed edge
void add_edge (Graph *g, int from, int to) {
	Edge* edge = (Edge*)malloc(sizeof(Edge));
	edge->next = NULL;
	edge->previous = NULL;
	edge->to = &(g->array[to]);
	
	if ((g->array + from)->head != NULL) {
		Edge* temp = g->array[from].head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = edge;
		edge->previous = temp;
		g->array[from].tail = edge;
	} else {
		g->array[from].head = edge;
		g->array[from].tail = edge;
	}
}

// implements breath first search and prints the results
void bfs (Graph* g, int origin) {
	printf("BFS ");
	
	Queue* head = create_queue(&(g->array[origin]));
	Queue* tail = head;
	head->node->visited = -1; // in queue
	
	Queue* qtemp = NULL;
	Queue* current = NULL;
	
	Edge* etemp = NULL;
	
	// Queue nodes are added at the head and dequeued at the tail
	while (tail != NULL) {
		current = tail;
		etemp = current->node->tail;
		
		while (etemp != NULL) {
			if (etemp->to->visited == 0) {
				qtemp = head;
				head = create_queue(etemp->to);
				head->next = qtemp;
				qtemp->previous = head;
				head->node->visited = -1; // in stack
			} etemp = etemp->previous;
		}
		
		tail = tail->previous;
		if (tail != NULL) tail->next = NULL;
		
		current->node->visited = 1; // done visiting node
		printf(" %c ", current->node->number + 'A');
		free(current);
	}
	
	unvisit_graph(g); // mark all nodes unvisited
	
	printf("\n");
}

// implements depth first search and prints the results
void dfs (Graph* g, int origin) {
	printf("DFS:");
	
	Stack* head = create_stack(&(g->array[origin]));
	head->node->visited = -1; // in stack
	
	Stack* stemp = NULL;
	Stack* current = NULL;
	
	Edge* etemp = NULL;
	
	while (head != NULL) {
		current = head;
		head = head->next;
		etemp = current->node->head;
		
		while (etemp != NULL) {
			if (etemp->to->visited == 0) {
				stemp = head;
				head = create_stack(etemp->to);
				head->next = stemp;
				head->node->visited = -1; // in stack
			} etemp = etemp->next;
		}
		
		current->node->visited = 1; // done visiting node
		printf(" %c ", current->node->number + 'A');
		free(current);
	}
	
	unvisit_graph(g); // mark all nodes unvisited
	
	printf("\n");
}

// delete the graph and all its data structures
void delete_graph (Graph* g) {
	Edge* temp = NULL;
	Edge* temp2 = NULL;
	
	for (int i = 0; i < g->num_nodes; i++) {
		temp = g->array[g->num_nodes - (i + 1)].head;
		
		while (temp != NULL) {
			temp2 = temp;
			temp = temp->next;
			
			// Free the Edge
			free(temp2);
		}
	}
	
	// Free the Node Array
	free(g->array);
	
	// Free the Graph
	free(g);
}