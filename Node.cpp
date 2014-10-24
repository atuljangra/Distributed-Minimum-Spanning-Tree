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
            if (!_mq._queue.empty()) {
                curMessage = _mq._queue.front();
                _mq._queue.pop();
            }
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

Edge * Node::_findEdgeForNode(Node *n) {
    for (vector<Item>::iterator it = _neighbours.begin();
            it != _neighbours.end(); it++) {
        Node *node = (Item(*it))._node;
        if (n == node) {
            return (Item (*it))._edge;
        }
    }
    return NULL;
}

Node* Node::_findNodeForEdge(Edge *e) {
    for (vector<Item>::iterator it = _neighbours.begin();
            it != _neighbours.end(); it++) {
        Edge *edge= (Item(*it))._edge;
        if (e  == edge) {
            return (Item (*it))._node;
        }
    }
    return NULL;
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
        _connect(&m);
    }
    else if (m._code == INITIATE) {
        _initiate(&m); 
    }
    else if (m._code == TEST) {
        _test(&m);
    }
    else if (m._code == REPORT) {
        _report(&m);
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

void Node::_connect(Message *m) {
    stringstream ss;
    ss.str(m->_msg);
    int level;
    ss >> level;
    cout << getID() << " received connect call, param:" << level << endl;
    
    // If I am sleeping, I need to wake the fuck up, it's 2014 already.
    if (_state == SLEEPING) {
        cout << " Trying to wake up " << getID() << endl;
        _wakeUp();
    }
    Node *sender = m -> sender; 
    Edge *e = _findEdgeForNode(sender);
    if (level < _levelNumber) {
        // Mark this edge as BRANCH
        e -> setState(BRANCH); 
        // Send initiate request.
        Message *msg = new Message();
        msg -> createInitiateRequest(_levelNumber, _fragmentName, _state, this);
        sender -> addMessage(msg);
        if (getState() == FIND)
            _findCount++;

    } else if (e -> getState() == BASIC){
        // Move message to end of queue.
        unique_lock<mutex> lock(_mq._mutex);
        Message front = _mq._queue.front();
        _mq._queue.pop();
        _mq._queue.push(front);
    }
    else {
        // Send initiate requests.
        Message *msg = new Message();
        cout << getID() << " Sending Initiate to " << sender->getID() 
            << " param: " << _levelNumber + 1 << " " <<  e -> getWeight() << " " << FIND << endl;
        msg -> createInitiateRequest(_levelNumber + 1, e -> getWeight(), FIND, this);
        sender -> addMessage(msg);
    }
}

void Node::_initiate(Message *msg) {
    Node *sender = msg -> sender;
    stringstream ss;
    int level, fragName, state;
    ss.str(msg -> _msg);
    ss >> level >> fragName >> state;
    cout << getID() << " received initiate " << sender -> getID() 
        << " param: " << level << " " << fragName << " " << state  << " " << msg->_msg << endl; 
    
    _levelNumber = level;
    _fragmentName = fragName;
    _state = state;
    Edge *e = _findEdgeForNode(sender);
    _inBranch = e;
    _bestEdge = NULL;
    _bestWeight = INT_MAX;


     for (vector<Item>::iterator it = _neighbours.begin();
            it != _neighbours.end(); it++) {
        Edge *edge = (Item(*it))._edge;
        Node *node = _findNodeForEdge(edge);
        cout << "Node is " << node->getID() << endl;
        if (node != sender && edge -> getState() == BRANCH) {
            // Send initiate requests.
            Message *msg = new Message();
            cout << getID() << " BRANCH Sending Initiate to " << sender->getID() 
                << " param: " << level << " " <<  fragName << " " << state << endl;
            msg -> createInitiateRequest(level, fragName, state, this);
            node -> addMessage(msg);
            if (state == FIND) {
                _findCount++;
            }
        }
     }
     if (_state == FIND) {
         cout << getID() << " Executing test" << endl;
         _procedureTest();
     }
}

void Node::_procedureTest() {
    Edge *minEdge = NULL;
    Node *minNode = NULL;
    int minWeight;
    for (vector<Item>::iterator it = _neighbours.begin();
            it != _neighbours.end(); it++) {
        Edge *edge = (Item(*it))._edge;
        Node *node = (Item(*it))._node;
        if (edge -> getState() == BASIC && edge -> getWeight() < minWeight) {
            minEdge = edge;
            minNode = node;
            minWeight = edge -> getWeight();
        }
    }
    if (minEdge != NULL && minNode != NULL) {
        _testEdge = minEdge;
        // Send test message on edge.
        Message *msg = new Message();
        cout << getID() << " Sending Test to " << minNode ->getID() 
            << " param: " << _levelNumber << " " << _fragmentName <<  endl;
        msg -> createTestRequest(_levelNumber, _fragmentName, this);
        minNode -> addMessage(msg);
    }
    else {
        _testEdge = NULL;
        _procedureReport();
    }
       

}

void Node::_procedureReport() {
    if (_findCount == 0 && _testEdge == NULL) {
        _state = FOUND;
        // Send report on the inbranch.
        Node *rec = _findNodeForEdge(_inBranch);
        Message *msg = new Message();
        msg -> createReportRequest(_bestWeight, this);
        rec -> addMessage(msg);
    }

}

void Node::_test(Message *m) {
    cout << "EXECUTING TEST" << endl;
}

void Node::_report(Message *m) {
    cout << "EXECUTING REPORT " << endl;

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
    msg -> createConnectRequest(_levelNumber, this);
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
