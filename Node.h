#ifndef NODE_H
#define NODE_H

#include <thread>
#include <vector>

// Irem for the gloabl adjacency list.
// TODO: Sematically this is not a good place.
class Node;
class Edge;
struct Item {
    Node *_node;
    Edge *_edge;
};

class Graph;
// This is a single node of the graph connected by an edge.
class Node {
    private:
        // pointer to the const global shared structure.
        const Graph *_graph;
        int _id;
        std::vector <Item> _neighbours;
    public:
        Node(int id) { _id = id;}
        void setNeighbours(std::vector<Item>);

};

#endif
