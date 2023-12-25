# Assignment 4 - Searching with Graphs

## Task 1
Implement a simple Graph and perform Depth First Search (DFS) and Breadth First Search (BFS) on the graph. (Using an Adjacency List)

Compile command:
gcc -Wall t1.c t1_test.c -o t1

Run command:
./t1

## Task 2
Implement a weighted Graph and perform Dijkstra Search on the Graph. (Using an Adjacency Matrix)

Compile command:
gcc -Wall t2.c t2_test.c -o t2

Run command:
./t2

## Task 3
Dublin Bus now provides real-time updates on the location and expected time of arrival for their buses. Google Maps use this information to advise you on the best sequence of buses/trains to take in order to reach your desired destination in the shortest possible time. This is achieved by viewing Dublin as being comprised of a number of nodes in a graph (locations) and edges between those nodes (roads/bus routes/train tracks). Each edge has a weight which depends on how long it will take you to travel towards your intended destination via that route. Given nodes, edges and weights, Dijkstra’s algorithm can be used to determine the optimal route to get you from where you are to where you want to be.

For this assignment you have been provided with two files – one contains a list of all bus stops in Dublin (nodes) and the other contains a list of routes between those bus stops (edges). The weights on each of the edges is the distance in metres between each bus stop. 

Your task is to load the data from both files and use them to build a graph which models the public transport system of Dublin city. Then, using Dijkstra’s algorithm on the graph, print the optimal sequence of bus stops from a given source to a given destination.

Compile command:
gcc -Wall t3.c t3_test.c -o t3

Run command:
./t3 vertices.csv edges.csv

Try stop 300 to stop 253.