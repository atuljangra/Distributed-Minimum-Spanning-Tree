#ifndef EDGE_H
#define EDGE_H

#include <queue>
#include <condition_variable>
#include <mutex>

#include "Node.h"


// Need to change exactly how a message isw delivered. 
// We cannot have a thread waiting for mutilple condition variables.
// This will not be efficient.
// Some solutions would be:
// 1. Have a queue and condition variable  at each node and have the other
// node's thread insert the message into the queue. But this would disturb the
// semantic.
// 2. Have a concept of edge delivery. Semantically edge is a network, and the
// two processes does not manually do the addition of message to the queue. We
// can create a new thread to transfer the message through the edge or we can
// have one thread per edge with one condition variable that will do this job.
class Pipe {
    private: 
        NodeID _id;
    public: 
        std::queue<Message> _queue;
        std::mutex _mutex;
        Pipe(NodeID id);
        NodeID getID() { return _id;}
        void writeMsg(Message *msg);
        Message *readMsg();
};
// Use notify and stuff to wake the sleeping thread.

// States for the edges.
#define REJECTED 0
#define BRANCH 1
#define BASIC 2

// Locking pattern:
// Node lock -> Edge lock.
// We should never take node lock, while taking a edge lock.

// An edge is a message passing system. Messages can be passed only between two
// nodes connected by an edge.
class Edge {
    private:
        Node *_a;
        Node *_b;
        Pipe *_pipe_a;
        Pipe *_pipe_b;
        int _weight;
        int _state;
        std::mutex _mu;
    public:
        Edge(Node *a, Node *b, int w);
        Pipe * getPipeA() { return _pipe_a; }
        Pipe * getPipeB() { return _pipe_b; }
        void sendMessage(Pipe * pipe, Message *msg);
        int getWeight() { return _weight; }
        ~Edge();


        int getState();
        void setState(int);
};

#endif
