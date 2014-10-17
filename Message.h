#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

#define PRINT -1
#define WAKEUP 0
#define CONNECT 1
class Node;
class Message {
    public:
        Message(int, std::string);
        int _code;
        Node *sender;
        std::string _msg;
        std::string getMessage();
        ~Message();
        Message(const Message &m) {
            _code = m._code;
            _msg = m._msg;
            sender = m.sender;        
        }

        Message() {
            _code = -1;
            _msg = "NULL";
            sender = NULL;
        }
        Message(int code) {
            _code = code;
            _msg = "NULL";
            sender = NULL;
        }

        /*
         * Message creaters.
         * Modify already instantiated Message.
        */
         Message * createWakeUpMessage();
         Message * createPrintRequest();
         Message * createConnectRequest(int level, Node *node);
};

#endif
