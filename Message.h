#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

#define PRINT -1
#define WAKEUP 0
#define CONNECT 1
#define INITIATE 2
#define TEST 3
#define REPORT 4
#define ACCEPT 5
#define REJECT 6

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
        void createWakeUpMessage();
        void createPrintRequest();
        void createConnectRequest(int level, Node *node);
        void createInitiateRequest(int level, int fragmentName, int state, Node *n);
        void createTestRequest(int level, int fragName, Node *n);
        void createAcceptRequest(Node *n);
        void createReportRequest(int bestEdge, Node *n);
        void createRejectRequest(Node *n);
};

#endif
