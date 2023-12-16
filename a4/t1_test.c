#include "t1.h"
#include <stdlib.h>
#include <stdio.h>

// converts an upper case character (A-Z) to a numerical value (between 0 and 25) 
static int char2val ( char c ) {
	if ( c < 'A' || c > 'Z' ) {
		return -1;
	}

	return c-'A';
}

int main(){
    int num_nodes = 6;
    Graph *graph = create_graph(num_nodes);
	printf("graph created\n");
	
	if (graph == NULL) printf("graph is NULL\n");
   
    add_edge(graph, char2val('A'), char2val('E'));
	printf("edge added A-E\n");
    add_edge(graph, char2val('B'), char2val('D'));
	printf("edge added B-D\n");
    add_edge(graph, char2val('A'), char2val('D'));
	printf("edge added A-D\n");
    add_edge(graph, char2val('A'), char2val('B'));
	printf("edge added A-B\n");
    add_edge(graph, char2val('B'), char2val('C'));
	printf("edge added B-C\n");
    add_edge(graph, char2val('C'), char2val('B'));
	printf("edge added C-B\n");
    add_edge(graph, char2val('E'), char2val('D'));
	printf("edge added E-D\n");
    add_edge(graph, char2val('D'), char2val('F'));
	printf("edge added D-F\n");
    add_edge(graph, char2val('F'), char2val('C'));
	printf("edge added F-C\n");
    add_edge(graph, char2val('C'), char2val('D'));
	printf("edge added C-D\n");

    dfs(graph, char2val('A'));
	printf("DFS Complete\n");
    bfs(graph, char2val('A'));
	printf("BFS Complete\n");

    delete_graph(graph);
	printf("Graph Deleted\n");

}