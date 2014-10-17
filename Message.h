#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

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
};

#endif
