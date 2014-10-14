#include <iostream>
#include <unordered_map>
#include <vector>

#include "Edge.h"
#include "Node.h"
// This is the main shared memory structure that will be used by different
// threads for cummuincation.
// This would be singleton class.
struct listItem {
    Node *node;
    std::vector<Item> list;
};

class Graph {
    private:
       static Graph * _instance;
       // Making the constructor private so that no one else can create a new
       // instance.

       // Adjacency listrepresenting graph.
       // Each node is given it's list only.
       std::vector<listItem> adj_list;
       Graph() { };
    public:
       static Graph * getInstance() {
           if (_instance == 0)
               _instance = new Graph();
           return _instance;
       }
       void addNodes(int i, int j);
       Edge *getEdge(int i, int j);
};

