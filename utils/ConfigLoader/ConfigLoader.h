

#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H



#include <string>
#include <unordered_map>

class ConfigLoader {
public:
    static std::unordered_map<std::string, std::string> loadRSSConfig(const std::string& configPath);
};

#endif //CONFIGLOADER_H
