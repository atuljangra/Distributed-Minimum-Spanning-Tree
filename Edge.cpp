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
 * Edge methods.
 */
Edge::Edge(Node *a, Node*b) {
    _a = a;
    _b = b;

    // Initialize Queue.

    // Initialize mutex and cv.

}
