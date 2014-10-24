#ifndef NODE_H
#define NODE_H

#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>

#include "Message.h"

// Item for the gloabl adjacency list.
// TODO: Sematically this is not a good place.
class Node;
class Edge;
struct NodeID {
    int id;
};


struct Item {
    Node *_node;
    Edge *_edge;
    Item(Node *n, Edge *e) {
        _node = n;
        _edge = e;
    }
    Item(const Item &it) {
        _node = it._node;
        _edge = it._edge;
    }
};

struct mq {
    std::queue<Message> _queue;
    std::mutex _mutex;
    std::condition_variable _cv;
};
class Graph;

// States for nodes.
#define DEAD -1
#define SLEEPING 0
#define FIND 1
#define FOUND 2
// This is a single node of the graph connected by an edge.
class Node {
    private:
        std::vector <Item> _neighbours;
        int _state;
        mq _mq;
        std::thread _thread;
        int _levelNumber;
        int _findCount;
        int _fragmentName;
        Edge *_inBranch;
        Edge *_bestEdge;
        int _bestWeight;
        Edge *_testEdge; 
        
        // This will be the main listerner that will handle the execution of
        // thread.
        void _threadListener();
        std::vector<Item>::iterator _minimumWeightNode();
        Edge * _findEdgeForNode(Node *n);
        Node * _findNodeForEdge(Edge *n);
        void _printList(std::vector<Item>);
        void _wakeUp();
        void _processMessage(Message m);
        void _printAndPerculate();
        void _connect(Message *m);
        void _initiate(Message *m);
        void _procedureTest();
        void _procedureReport();
        void _report(Message *m);
        void _test(Message *m);
        void _accept(Message *m);
        void _reject(Message *m);
        void _procedureChangeCore();
        void _changeCore(Message *m);

    public:
        void addMessage(Message *msg); 
        NodeID _id;
        Node(int id) {
            NodeID nodeID;;
            nodeID.id = id;
            _id = nodeID;
            _state = DEAD;
        }
        int getState() { return _state;}
        int getID() { return _id.id; }
        void setNeighbours(std::vector<Item>);
        void printEdges();
        // This will actually create the thread and mark the thread as asleep.
        void start();
        int getLevelNumber() { return _levelNumber; }
        ~Node();
};

#include "Edge.h"
#endif
