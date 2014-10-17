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
Edge::Edge(Node *a, Node*b, int w) {
    _a = a;
    _b = b;

    _weight = w;
    // Initialize Queue.
    _pipe_a = new Pipe(_a -> _id);
    _pipe_b = new Pipe(_b -> _id);
    // Initialize mutex and cv.

}

void Edge::sendMessage(Pipe *pipe, Message *msg) {
    pipe -> writeMsg(msg);
}

// TODO Do we need this to be thread safe.
int Edge::getState() {
    unique_lock<mutex> lock(_mu);
    return _state;
}

void Edge::setState(int state) {
    unique_lock<mutex> lock(_mu);
    _state = state;

}
