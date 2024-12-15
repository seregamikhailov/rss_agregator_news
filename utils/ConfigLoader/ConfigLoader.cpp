#include "ConfigLoader.h"
#include <json.hpp>
#include <fstream>
#include "ConfigLoadException.h"
using json = nlohmann::json;

std::unordered_map<std::string, std::string> ConfigLoader::loadRSSConfig(const std::string &configPath) {
    std::unordered_map<std::string, std::string> rssMap;
    std::ifstream file(configPath);
    if (!file) {
        throw ConfigLoadException("Не удалось открыть файл конфигурации: " + configPath);
    }
    json config;
    try {
        file >> config;
    } catch (const json::parse_error &e) {
        throw ConfigLoadException("Ошибка парсинга файла конфигурации: " + std::string(e.what()));
    }
    try {
        for (const auto &[key, value]: config.items()) {
            if (!value.is_string()) {
                throw ConfigLoadException("Ожидалась строка для ключа: " + key);
            }
            rssMap[key] = value.get<std::string>();
        }
    } catch (const std::exception &e) {
        throw ConfigLoadException("Ошибка обработки содержимого файла конфигурации: " + std::string(e.what()));
    }
    return rssMap;
}
