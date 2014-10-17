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
    cout << getID() << " Hello! " << endl;
    Message curMessage;
    _state = SLEEPING;
    while (1) {
        unique_lock<mutex> locker(_mq._mutex);
        cout << getID() << " checking queue" << endl;
        // Check queue if there is any message.
        bool isEmpty = _mq._queue.empty();
        if (!isEmpty) {
            curMessage = _mq._queue.front();
            _mq._queue.pop();
        } else {
            cout << getID() << " Waiting " << endl;
            _mq._cv.wait(locker);
        }
    
    
    thread::id id = this_thread::get_id();
    cout << "Thread " << id << " up for node " << getID() << endl;
    // When someonenotifies us, just print the edges.
    printEdges();
    cout << "Ending .... thread " << id << " for node " << getID() << endl;
    _state = FIND; 
    // add message to the neighbours too.
    for (vector<Item>::iterator it = _neighbours.begin(); it != _neighbours.end(); it++) {
        Node * n = (Item(*it))._node;
        if (n -> getState() == SLEEPING) 
            n->addMessage(NULL);
        
    }
    }
}


void Node::addMessage(Message *msg) {
    unique_lock<mutex> lock(_mq._mutex);
    // Add message to the queue.
    // Need a copy constructor.
    // TODO check if this is working fine.
    Message m;
    if (msg != NULL) {
        m = *msg;
    }
    _mq._queue.push(m);
    //notify all wiating on this. Essentially there will be only one guy waiting
    //on this.
    cout << "notifying " << getID() << endl;
    _mq._cv.notify_all();
    cout << getID() << "notified " << endl;
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
