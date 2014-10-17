#ifndef NODE_H
#define NODE_H

#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
// Item for the gloabl adjacency list.
// TODO: Sematically this is not a good place.
class Node;
class Edge;
struct NodeID {
    int id;
};

class Message {
    public:
        Message(int, std::string);
        int _code;
        std::string _msg;
        std::string getMessage();
        ~Message();
        Message(const Message &m) {
                _code = m._code;
                _msg = m._msg;
        }
        Message() {
            _code = -1;
            _msg = "NULL";
        }
};

struct Item {
    Node *_node;
    Edge *_edge;
    Item(Node *n, Edge *e) {
        _node = n;
        _edge = e;
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
        
        // This will be the main listerner that will handle the execution of
        // thread.
        void _threadListener();
        void _printList(std::vector<Item>);
        std::thread _thread;
        int _state;
        void _wakeUp();
        mq _mq;
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

        ~Node();
};

#include "Edge.h"
#endif
