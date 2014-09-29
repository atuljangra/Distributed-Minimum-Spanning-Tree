#ifndef EDGE_H
#define EDGE_H

#include <queue>
#include <condition_variable>
#include <mutex>

#include "Node.h"
class Message {
    public:
        Message(int, std::string);
        int _code;
        std::string _msg;
        std::string getMessage();
        ~Message();
};

// An edge is a message passing system. Messages can be passed only between two
// nodes connected by an edge.
class Edge {
    private:
        Node *_a;
        Node *_b;
    public:
        Edge(Node *a, Node *b);
        std::queue<Message> _message_queue;
        std::condition_variable _cv;
        std::mutex _mu;
        ~Edge();
};

#endif
