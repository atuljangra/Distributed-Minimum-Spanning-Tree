#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

#define PRINT -1
#define WAKEUP 0

class Message {
    public:
        Message(int, std::string);
        int _code;
        std::string _msg;
        std::string getMessage();
        ~Message();
        Message(const Message &m) {
                _code = m._code;
                _msg = m._msg;
        }
        Message() {
            _code = -1;
            _msg = "NULL";
        }
        Message(int code) {
            _code = code;
            _msg = "NULL";
        }

        /*
         * Message creaters.
         * Modify already instantiated Message.
        */
         Message * createWakeUpMessage();
         Message * createPrintRequest();
};

#endif
