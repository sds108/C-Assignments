#include "t3.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

// Global Variables
Graph* g = NULL;
int* alias_list = NULL;
int alias_list_size;







// creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void create_graph (Node* head, int num_nodes) {
	// create graph for global variable g
	g = (Graph*)malloc(sizeof(Graph));
	g->num_nodes = num_nodes;
	
	// create matrix
	g->matrix = (int**)malloc(num_nodes * sizeof(int*));
	
	// create rows
	for (int i = 0; i < num_nodes; i++) {
		g->matrix[i] = (int*)malloc(num_nodes * sizeof(int));
		
		// initialize all coordinates with 0
		for (int j = 0; j < num_nodes; j++) {
			g->matrix[i][j] = 0;
		}
	}
	
	// create node pointer array
	g->array = (Node**)malloc(num_nodes * sizeof(Node*));
	
	// Fill pointer array with linked list pointers and fill alias list with aliases
	Node* current = head;
	int node_counter = 0;
	while (current != NULL) {
		g->array[node_counter] = current;
		//printf("%4i %-20s%-10s%-10s\n", g->array[node_counter]->stopID, g->array[node_counter]->name, g->array[node_counter]->latitude, g->array[node_counter]->longitude);
		alias_list[current->stopID] = node_counter;
		
		current = current->next;
		node_counter++;
	}
}

// adds an undirected weighted edge between from and to
void add_edge (int from, int to, int weight) {
	int actual_from = alias_list[from];
	int actual_to = alias_list[to];
	
	g->matrix[actual_from][actual_to] = weight;
	g->matrix[actual_to][actual_from] = weight;
}	

// implements the dijkstra algorithm and prints the order in which the nodes are made permanent, and the length of the shortest path between the origin node and all the other nodes
void shortest_path (int startNode, int endNode) {
	// check in range
	if (startNode < 0 || startNode >= alias_list_size) {
		printf("Stop %i does not exist\n", startNode);
		return;
	}
	
	if (endNode < 0 || endNode >= alias_list_size) {
		printf("Stop %i does not exist\n", endNode);
		return;
	}
	
	// Convert startNode to origin, and endNode to destination
	int origin = alias_list[startNode];
	int destination = alias_list[endNode];
	
	if (origin == -1) printf("Stop %i does not exist\n", startNode);
	if (destination == -1) printf("Stop %i does not exist\n", endNode);
	if (origin == -1 || destination == -1) return;
	
	// set origin distance to 0
	g->array[origin]->distance = 0;
	
	// Set current & next to origin
	int current = origin;
	
	// Minimum visited
	int min_distance = INT_MAX;
	int min_visited = origin;
	
	
	int all_permanent = 0;
	int any_to_visit = 0;
	
	do {
		// set current to next closest visited
		current = min_visited;
		g->array[current]->visited = 0;
		
		// set current to permanent
		g->array[current]->permanent = 1;
		
		// go through neighbours of current node and update distances if necessary
		for (int i = 0; i < g->num_nodes; i++) {
			// if neighbour of current
			if (g->matrix[current][i] > 0) {
				// if not permanent
				if (g->array[i]->permanent != 1) {					
					// if current distance from origin through current is shorter than the distance at the moment, update the distance and set the predecessor
					if (g->array[i]->distance > g->array[current]->distance + g->matrix[current][i]) {
						g->array[i]->predecessor = current;
						g->array[i]->distance = g->array[current]->distance + g->matrix[current][i];
						
						// set to visited 
						g->array[i]->visited = 1;
					}
				}
			}
		}
		
		// go through visited and pick closest to origin
		min_distance = INT_MAX;
		
		for (int i = 0; i < g->num_nodes; i++) {
			// filter visited impermanent nodes
			if (g->array[i]->visited == 1 && g->array[i]->permanent != 1) {
				if (g->array[i]->distance < min_distance) {
					min_distance = g->array[i]->distance;
					min_visited = i;
				}
			}
		}
		
		// check if all nodes are permanent
		all_permanent = 1;
		for (int i = 0; i < g->num_nodes; i++) {
			if (g->array[i]->permanent != 1) {
				all_permanent = 0;
				break;
			}
		}
		
		// check if all nodes are visited
		any_to_visit = 1;
		for (int i = 0; i < g->num_nodes; i++) {
			if (g->array[i]->visited != 1) {
				any_to_visit = 0;
				break;
			}
		}
	} while (!all_permanent && !any_to_visit);
	
	
	if (g->array[destination]->predecessor != -1) {
		int curr = destination;
		Stack* head = NULL;
		Stack* temp = NULL;
		while (curr >= 0) {
			temp = head;
			head = (Stack*)malloc(sizeof(Stack));
			head->next = temp;
			head->index = curr;
			curr = g->array[curr]->predecessor;
		}
		
		if (head != NULL) {
			temp = NULL;
			Stack* currStack = head;
			while (currStack != NULL) {
				temp = currStack;
				//printf("%4i %-19s%-9f %-9f\n", g->array[currStack->index]->stopID, g->array[currStack->index]->name, g->array[currStack->index]->latitude, g->array[currStack->index]->longitude);
				printf("%i %s\n", g->array[currStack->index]->stopID, g->array[currStack->index]->name);
				currStack = currStack->next;
				free(temp);
			}
		}
	} else printf("Could not find a path between %i and %i\n", startNode, endNode);
}

void free_memory () {
	// free rows and nodes
	for (int i = 0; i < g->num_nodes; i++) {
		free(g->matrix[i]);
		free(g->array[i]);
	}
	
	// free matrix
	free(g->matrix);
	
	// free node array
	free(g->array);
	
	// free graph
	free(g);
}

void next_token (char* buffer, FILE* csv, int max_len) {
	int c;
	int n = 0;
	bool insideQuotes = false;
	
	while (1) {
		c = fgetc(csv);
		
		if (c == EOF) {
			buffer[n] = '\0';
			break;
		}
		
		else if (c == '\n') {
			buffer[n] = '\0';
			break;
		}
		
		else if (c == '\"') {
			insideQuotes = !insideQuotes;
		}
		
		else if (c == ',') {
			if (insideQuotes) {
				buffer[n] = c;
				n++;
			} else {
				buffer[n] = '\0';
				break;
			}
		}
		
		else {
			buffer[n] = c;
			n++;
		}
		
		if (n + 1 >= max_len) {
			buffer[n] = '\0';
			break;
		}
	}
	
	if (n == 0) {
		buffer[0] = '0';
		buffer[1] = '\0';
	}
}

//  Reads the edges and adds them to the adjacency matrix - returns 1 if file was successfully read and 0 if not.
int load_edges (char *fname) {
	FILE *f;
	char buf[MAX_STRING_SIZE];
	int paramCounter = 0;
	bool skippedLine = false;
	int edge_counter = 0;
	
	// Params for add_edge function
	int from;
	int to;
	int weight;

	// boiler plate code to ensure we can open the file
	f = fopen(fname, "r");
	
	if (!f) { 
		printf("Unable to open %s\n", fname);
		return 0; 
	}
	
	if (g == NULL) { 
		printf("Graph Pointer is NULL\n");
		return 0; 
	}
	
	// read until the end of the file
	while (!feof(f)) {
		next_token(buf, f, MAX_STRING_SIZE);
		
		if (strlen(buf) == 0) {
			buf[0] = '0';
			buf[1] = '\0';
		}
		
		if (skippedLine) {
			switch (paramCounter) {
				case 0:
					from = atoi(buf);
					break;
				case 1:
					to = atoi(buf);
					break;
				case 2:
					weight = atoi(buf);
					break;
			}
		}
		
		if (paramCounter >= 2 && !feof(f)) {
			if (skippedLine) add_edge(from, to, weight);
			edge_counter++;
			skippedLine = true;
			paramCounter = -1;
		}
		
		paramCounter++;
	}
	
	printf("Loaded %i edges\n", edge_counter);
	
	// always remember to close your file stream
	fclose(f);
	
	return 1;
}

//  Reads the vertices and add them to the linked list - returns 1 if file was successfully read and 0 if not.
int load_vertices (char *fname) {
	FILE *f;
	char buf[MAX_STRING_SIZE];
	int paramCounter = 0;
	bool skippedLine = false;
	Node* head = NULL;
	Node* temp = NULL;
	
	// node counter to make a matrix later
	int node_counter = 0;
	int max_id = 0;

	// boiler plate code to ensure we can open the file
	f = fopen(fname, "r");
	
	if (!f) { 
		printf("Unable to open %s\n", fname);
		return 0; 
	}
	
	// read until the end of the file
	while (!feof(f)) {
		next_token(buf, f, MAX_STRING_SIZE);
		
		if (strlen(buf) == 0) {
			buf[0] = '0';
			buf[1] = '\0';
		}
		
		if (skippedLine) {
			if (head != NULL) {
				switch (paramCounter) {
					case 0:
						head->stopID = atoi(buf);
						
						// update max_id
						if (head->stopID > max_id) max_id = head->stopID;						
						break;
					case 1:
						strcpy(head->name, buf);
						break;
					case 2:
						head->latitude = atof(buf);
						break;
					case 3:
						head->longitude = atof(buf);
						break;
				}
			}
		}
		
		if (paramCounter >= 3 && !feof(f)) {
			node_counter++;
			
			temp = head;
			
			head = (Node*)malloc(sizeof(Node));
			head->visited = 0;
			head->permanent = 0;
			head->distance = INT_MAX;
			head->predecessor = -1;
			
			head->next = temp;
			
			skippedLine = true;
			paramCounter = -1;
		}
		
		paramCounter++;
	}
	
	// Once we've made the linked list
	// We create a graph and an alias list
	printf("Loaded %i vertices\n", node_counter);
	max_id++;
	
	alias_list_size = max_id;
	
	// fill alias_list with -1
	alias_list = (int*)malloc(max_id * sizeof(int));
	
	for (int i = 0; i < max_id; i++) {
		alias_list[i] = -1;
	}
	
	// Create Graph
	create_graph(head, node_counter);
	
	// always remember to close your file stream
	fclose(f);

	return 1;
}