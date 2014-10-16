#include <iostream>

#include "Node.h"

using namespace std;

void Node::setNeighbours(vector<Item> v) {
    _neighbours = v;
}

void Node::start() {
    _thread = thread(&Node::_threadListener, this);
}

void Node::_threadListener() {
    // For now just print some information and exit.
    std::cout << getID() << " Hello! " << std::endl;
    printEdges();

    
}

void Node::_printList(vector<Item> v) {   
    for (vector<Item>::iterator it = v.begin(); it != v.end(); it++) {
        Item item = *it;
        cout << getID() << " -> " << item._node->getID() << ":" << item._node << "\t" 
            << item._edge->getWeight() << ":" << item._edge << endl;
    }
}

void Node::_wakeUp() {


}

void Node::printEdges() {
    _printList(_neighbours);
}

Node::~Node() {
    cout << "Thou shall wait" << endl;
    // We need to gracefully exit.
    // Although all the output will be shown by the root node, but still our
    // main program will wait for all the spawned threads
    _thread.join();
}
