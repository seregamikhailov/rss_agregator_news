#ifndef NOTFOUNDEXCEPTION_H
#define NOTFOUNDEXCEPTION_H
#include <stdexcept>

class NotFoundException : public std::runtime_error {
public:
    explicit NotFoundException(const std::string &message) : std::runtime_error(message) {
    }
};
#endif //NOTFOUNDEXCEPTION_H
