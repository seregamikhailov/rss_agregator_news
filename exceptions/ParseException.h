
#ifndef PARSEEXCEPTION_H
#define PARSEEXCEPTION_H
#include <stdexcept>

class ParseException : public std::runtime_error {
public:
    explicit ParseException(const std::string &message) : std::runtime_error(message) {}
};

#endif //PARSEEXCEPTION_H
