#include <sstream>
#include "Message.h"

using namespace std;

void Message::createWakeUpMessage() {
    _code = WAKEUP;
}

void Message::createPrintRequest() {
    _code = PRINT;
}

void Message::createConnectRequest(int level, Node *node) {
    _code = CONNECT;
    stringstream ss;
    ss << level;
    _msg= ss.str();
    sender = node;
}

void Message::createInitiateRequest(int level, int fragName, int state, Node *n) {
    _code = INITIATE;
    stringstream ss;
    ss << level << " " << fragName << " " << state;
    _msg = ss.str();
    sender = n;
}

void Message::createTestRequest(int level, int fragName, Node *n) {
    _code = TEST;
    stringstream ss;
    ss << level << " " << fragName;
    _msg = ss.str();
    sender = n;
}

void Message::createReportRequest(int bestWt, Node *n) {
    _code = REPORT;
    stringstream ss;
    ss << bestWt;
    _msg = ss.str();
    sender = n;
}
