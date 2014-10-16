#include <iostream>
#include <unordered_map>
#include <vector>

#include "Edge.h"
#include "Node.h"
struct listItem {
    Node *node;
    std::vector<Item> edgeList;
    listItem(Node * n) {
		node = n;
	}
    Edge * getEdgeForNode(Node *node);
};

// This is the main shared memory structure that will be used by different
// threads for cummuincation.
// This would be singleton class.
class Graph {
    private:
       static Graph * _instance;
       // Making the constructor private so that no one else can create a new
       // instance.

       // Adjacency listrepresenting graph.
       // Each node is given it's list only.
       std::vector<listItem*> adj_list;
       Graph() { };
       int _num;
    public:
       static Graph * getInstance() {
           if (_instance == 0)
               _instance = new Graph();
           return _instance;
       }
       
       void createGraph(int num, std::vector<int> graph);
       void printGraph();
       // Every node will know about their neighbours and connecting edges only.
       void distributeGraph();
       // This will create the runnable threads and mark everyone as asleep.
       void runNodes();
};

