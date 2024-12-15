#ifndef CONFIGLOADEXCEPTION_H
#define CONFIGLOADEXCEPTION_H
#include <stdexcept>

class ConfigLoadException : public std::runtime_error {
public:
    explicit ConfigLoadException(const std::string &message) : std::runtime_error(message) {
    }
};
#endif //CONFIGLOADEXCEPTION_H
