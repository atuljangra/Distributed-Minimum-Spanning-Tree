#include <iostream>
#include <vector>
#include <unordered_map>

#include "Graph.h"

using namespace std;

Graph * Graph::_instance = 0;

unordered_map<int, Node *> nodeObjects;

Edge * listItem::getEdgeForNode(Node * node) {
    Edge *e = NULL;
    for (vector<Item>::iterator it = edgeList.begin(); it != edgeList.end(); it++) {
        Item item = *it;
        if (item._node == node)
            return item._edge;
    }
    return e;
}

/*
 * Functions for graph
 */ 
void printList(vector<Item> v) {   
    for (vector<Item>::iterator it = v.begin(); it != v.end(); it++) {
        Item item = *it;
        cout << item._node->getID() << ":" << item._node << "\t" 
            << item._edge->getWeight() << ":" << item._edge << endl;
    }
}

void Graph::createGraph(int num, std::vector<int> graph) {
	_num = num;
    // Add Nodes.
	for (int i = 0; i < num; i++) {
		Node *n = new Node(i);
        nodeObjects[i] = n;
        listItem *l = new listItem(n);
		// Ordered is maintained, thus this makes sense.
		// Otherwise using hash table would be our best bet.
		adj_list.push_back(l);
	}
	
	// Add edges.
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            // Edge from i -> j.
			int weight = graph[i * num + j];
            if (weight <= 0)
                continue;
            // Edge should be common.
            Edge *e = adj_list[j] -> getEdgeForNode(nodeObjects[i]);
            if (e == NULL) {
                e = new Edge(nodeObjects[i], nodeObjects[j], weight);
            }

            listItem *lI = adj_list[i];
            Item *item = new Item(nodeObjects[j], e);
            lI->edgeList.push_back(*item);
        }
    }
}


void Graph::printGraph() {
    for (int i = 0; i < _num; i++) {
        Node *n = adj_list[i]->node;

        cout << "Edges for " << i << ":" << n << endl;
        printList(adj_list[i] -> edgeList);
    }
}

void Graph::distributeGraph() {
    for (int i = 0; i < _num; i++) {
        Node *n = nodeObjects[i];
        n -> setNeighbours(adj_list[i] -> edgeList);
    }
}

void Graph::runNodes() {
    for (int i = 0; i < _num; i++) {
        nodeObjects[i]->start();
    }
        
}

void Graph::wakeOneNodeUp() {
    Message *msg = new Message();
    msg -> createWakeUpMessage(); 
    nodeObjects[0]->addMessage(msg);
}
