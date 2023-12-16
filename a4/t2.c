#include "t2.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void reset_graph (Graph* g) {
	for (int i = 0; i < g->num_nodes; i++) {
		g->array[i].visited = 0;
		g->array[i].permanent = 0;
		g->array[i].distance = INT_MAX;
		g->array[i].predecessor = -1;
	}
}

// creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
Graph* create_graph (int num_nodes) {
	// create graph
	Graph* g = (Graph*)malloc(sizeof(Graph));
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
	
	// create nodes
	g->array = (Node*)malloc(num_nodes * sizeof(Node));
	
	// initialize nodes
	for (int i = 0; i < num_nodes; i++) {
		g->array[i].visited = 0;
		g->array[i].permanent = 0;
		g->array[i].distance = INT_MAX;
		g->array[i].predecessor = -1;
	}
	
	return g;
}

// adds an undirected weighted edge between from and to
void add_edge (Graph *g, int from, int to, int weight) {
	g->matrix[from][to] = weight;
	g->matrix[to][from] = weight;
}	

// implements the dijkstra algorithm and prints the order in which the nodes are made permanent, and the length of the shortest path between the origin node and all the other nodes
void dijkstra (Graph* g, int origin) {
	// set origin distance to 0
	g->array[origin].distance = 0;
	
	// Set current & next to origin
	int current = origin;
	
	// Minimum visited
	int min_distance = INT_MAX;
	int min_visited = origin;
	
	
	int all_permanent = 0;
	
	do {
		// set current to next closest visited
		current = min_visited;
		
		// set current to permanent
		g->array[current].permanent = 1;
		
		// go through neighbours of current node and update distances if necessary
		for (int i = 0; i < g->num_nodes; i++) {
			// if neighbour of current
			if (g->matrix[current][i] > 0) {
				// if not permanent
				if (g->array[i].permanent != 1) {					
					// if current distance from origin through current is shorter than the distance at the moment, update the distance and set the predecessor
					if (g->array[i].distance > g->array[current].distance + g->matrix[current][i]) {
						g->array[i].predecessor = current;
						g->array[i].distance = g->array[current].distance + g->matrix[current][i];
						
						// set to visited 
						g->array[i].visited = 1;
					}
				}
			}
		}
		
		// go through visited and pick closest to origin
		min_distance = INT_MAX;
		
		for (int i = 0; i < g->num_nodes; i++) {
			// filter visited impermanent nodes
			if (g->array[i].visited == 1 && g->array[i].permanent != 1) {
				if (g->array[i].distance < min_distance) {
					min_distance = g->array[i].distance;
					min_visited = i;
				}
			}
		}
		
		// print current
		printf("%c ", current + 'A');
		
		// check if all nodes are permanent
		all_permanent = 1;
		for (int i = 0; i < g->num_nodes; i++) {
			if (g->array[i].permanent != 1) {
				all_permanent = 0;
				break;
			}
		}
	} while (!all_permanent);
	
	// skip a line
	printf("\n");
	
	// print distances betweent the origin and each node
	for (int i = 0; i < g->num_nodes; i++) {
		printf("The length of the shortest path between %c and %c is %i\n", origin + 'A', i + 'A', g->array[i].distance);
	}
}

void delete_graph (Graph* g) {
	// free rows
	for (int i = 0; i < g->num_nodes; i++) {
		free(g->matrix[i]);
	}
	
	// free matrix
	free(g->matrix);
	
	// free node array
	free(g->array);
	
	// free graph
	free(g);
}