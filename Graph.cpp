#include <iostream>
#include <vector>

#include "Graph.h"

Graph * Graph::_instance = 0;
/*
 * Functions for graph
 */
void Graph::addNodes(int i, int j) { 
    Node *a = new Node(i);
    Node *b = new Node(j);
    Edge *__attribute__((unused))edge = new Edge(a, b);
    // Add to the global list.
    //
    // Pass the list to both the nodes.

}

Edge * Graph::getEdge(int i, int j) {
    return NULL;

}

void Graph::createGraph(int num, std::vector<int> graph) {
	// Add Nodes.
	for (int i = 0; i < num; i++) {
		Node *n = new Node(i);
		listItem *l = new listItem(n);
		// Ordered is maintained, thus this makes sense.
		// Otherwise using hash table would be our best bet.
		adj_list.push_back(*l);
	}
	
	// Add edges.
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num,; j++) {
            // Edge from i to j.
			int weight = graph[i * num + j];
			Node *iNode = adj_list
			// We have already created an edge. Use that only.
			if (i > j) {
				Edge *e = adj_list[j].
			}
            cout << graph[i*num + j] << " ";
        }
    }
	
}
