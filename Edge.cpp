#include <iostream>
#include "Edge.h"

using namespace std;

/*
 * Message methods.
 */
Message::Message(int code, string message) {
    _code = code;
    _msg = message;
}

Message::~Message() {

}

/*
 * Pipe Methods.
 */
Pipe::Pipe(NodeID id) {
    _id = id;
}

void Pipe::writeMsg(Message *msg) {
    unique_lock<mutex> lock (_mutex);
    _queue.push(*msg);
}
/*
 * Edge methods.
 */
Edge::Edge(Node *a, Node*b) {
    _a = a;
    _b = b;

    // Initialize Queue.
    _pipe_a = new Pipe(_a -> _id);
    _pipe_b = new Pipe(_b -> _id);
    // Initialize mutex and cv.

}

void Edge::sendMessage(Pipe *pipe, Message *msg) {
    pipe -> writeMsg(msg);
}
