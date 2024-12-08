#include "ConfigLoader.h"
#include <json.hpp>
#include <fstream>
#include <iostream>
using json = nlohmann::json;
std::unordered_map<std::string, std::string> ConfigLoader::loadRSSConfig(const std::string& configPath) {
    std::unordered_map<std::string, std::string> rssMap;
    std::ifstream file(configPath);

    if (!file) {
        std::cerr << "Не удалось открыть файл конфигурации: " << configPath << std::endl;
        return rssMap;
    }

    json config;
    file >> config;

    for (auto it = config.begin(); it != config.end(); ++it) {
        rssMap[it.key()] = it.value();
    }
    return rssMap;
}
