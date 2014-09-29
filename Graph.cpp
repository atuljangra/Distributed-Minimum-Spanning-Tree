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

