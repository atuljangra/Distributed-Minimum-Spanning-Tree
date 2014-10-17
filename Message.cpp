#include <sstream>
#include "Message.h"

using namespace std;

Message * Message::createWakeUpMessage() {
    _code = WAKEUP;
    return this ;
}

Message * Message::createPrintRequest() {
    _code = PRINT;
    return this;
}

Message * Message::createConnectRequest(int level) {
    _code = CONNECT;
    stringstream ss;
    ss << level;
    _msg= ss.str();
    return this;
}
