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
