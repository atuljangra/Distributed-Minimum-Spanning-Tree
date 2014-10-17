#include <iostream>
#include <climits>
#include <sstream>

#include "Node.h"

using namespace std;


thread::id tid;
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
            // Someone will notify us and then we will check the queue.
            curMessage = _mq._queue.front();
            _mq._queue.pop();
        }
        locker.unlock() ;
        cout << getID() << "starting procedure " << endl;
        // By this point we have a message and we need to process it.
        _processMessage(curMessage);
        // TODO Add a death message.
    }
}

vector<Item>::iterator  Node::_minimumWeightNode() {
    int minWeight = INT_MAX;
    vector<Item>::iterator result;
    for (vector<Item>::iterator it = _neighbours.begin();
            it != _neighbours.end(); it++) {
        int wt = (Item(*it))._edge->getWeight();
        if (wt < minWeight) {
            minWeight = wt;
            result = it;
        }
    }
    cout << getID() << "min wt edge is -> " << ((Item )*result)._node->getID() << " wt: " << minWeight << endl;
    return result;
}

void Node::_processMessage(Message m) {
    // Decode the message.
    // Call the appropriate handler.
    
    // WakeUP message;
    if (m._code == WAKEUP) { 
        cout << getID() << " received wake up call " << endl; 
        _wakeUp();
    }
    else if (m._code == PRINT) { 
        cout << getID() << " received print call " << endl;
        _printAndPerculate();
    }
    else if (m._code == CONNECT) { 
        // Get the argument.
        stringstream ss;
        ss.str(m._msg);
        int level;
        ss >> level;
        cout << getID() << " received connect call, param:" << level << endl;
        _connect(level);
    }
    else {
        cout << " received invalid request " << endl;
    }
}

void Node::_printAndPerculate() {
    
    tid = this_thread::get_id();
    cout << "Thread " << tid << " up for node " << getID() << endl;
    // When someonenotifies us, just print the edges.
    printEdges();
    cout << "Ending .... thread " << tid << " for node " << getID() << endl;
    _state = FIND; 
    // add message to the neighbours too.
    for (vector<Item>::iterator it = _neighbours.begin(); it != _neighbours.end(); it++) {
        Node * n = (Item(*it))._node;
        if (n -> getState() == SLEEPING) { 
            Message *m = new Message();
            m -> createPrintRequest();
            n->addMessage(m);
        }
    }
}

void Node::_connect(int level) {
    // If I am sleeping, I need to wake the fuck up, it's 2014 already.


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
    cout << "Message is " << m._code << " " << m._msg << endl;
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
    vector<Item>::iterator minNodeIterator = _minimumWeightNode();
    Node *minNode = (*minNodeIterator)._node;
    Edge *minEdge = (*minNodeIterator)._edge;
    // Mark the connecting branch as BRANCH.
    minEdge->setState(BRANCH);
    
    _levelNumber = 0;
    
    _state = FOUND;
    _findCount = 0;
    
    // Send connect request to minNode.
    Message *msg = new Message();
    msg -> createConnectRequest(_levelNumber);
    cout << getID() << ": Sending connect request to " << minNode -> getID() << 
        " Level: " << _levelNumber << endl;
    minNode->addMessage(msg);
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
