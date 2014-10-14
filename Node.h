#ifndef NODE_H
#define NODE_H

#include <thread>
#include <vector>

// Irem for the gloabl adjacency list.
// TODO: Sematically this is not a good place.
class Node;
class Edge;

struct NodeID {
    int id;
};

struct Item {
    Node *_node;
    Edge *_edge;
};

class Graph;
// This is a single node of the graph connected by an edge.
class Node {
    private:
        // pointer to the const global shared structure.
        // Remove this.
        const Graph *_graph;
        std::vector <Item> _neighbours;
    public:
        NodeID _id;
        Node(int id) {
            NodeID nodeID;;
            nodeID.id = id;
            _id = nodeID;
        }
        void setNeighbours(std::vector<Item>);

};

#endif
