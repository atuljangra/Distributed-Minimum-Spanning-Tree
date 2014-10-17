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
    ~listItem() {
        std::cout << "deleting node " << node -> getID() << std:: endl;
        // Items for edgeList will be deleted automatically. 
        delete node;
    }
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

       ~Graph () {
           std::cout << "Deleting graph " << std::endl;
           for (std::vector<listItem *>::iterator it = adj_list.begin(); it != adj_list.end();
                   it++) {
               delete *it;


           }
           adj_list.clear();
           adj_list.shrink_to_fit();
       
       }

       void createGraph(int num, std::vector<int> graph);
       void printGraph();
       // Every node will know about their neighbours and connecting edges only.
       void distributeGraph();
       // This will create the runnable threads and mark everyone as asleep.
       void runNodes();
       void wakeOneNodeUp();
};

