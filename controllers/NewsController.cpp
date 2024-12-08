#include "NewsController.h"

#include <RSSService.h>

#include "ConfigLoader.h"

void NewsController::setupRoutes(httplib::Server &server,NewsService &newsService) {
    std::unordered_map<std::string, std::string> rssMap = ConfigLoader::loadRSSConfig(
        "/app/config/rss_sources.json");

    server.Get("/news", [&newsService,rssMap](const httplib::Request &req, httplib::Response &res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        try {
            std::string source = req.get_param_value("source");
            std::string keywords = req.get_param_value("keywords");
            int limit = req.has_param("limit") ? std::stoi(req.get_param_value("limit")) : 10;
            auto it = rssMap.find(source);
            if (it == rssMap.end()) {
                res.status = 400;
                res.set_content("Источник не найден", "text/plain");
                return;
            }

            auto items = newsService.getFilteredNews(it->second, keywords,limit);
            if (items.empty()) {
                res.set_content("[]", "application/json");
                return;
            }

            nlohmann::json responseJson = nlohmann::json::array();
            for (const auto &item: items) {
                responseJson.push_back(item.toJson());
            }
            res.set_content(responseJson.dump(4), "application/json");
        } catch (const std::exception &e) {
            res.status = 500;
            res.set_content("Ошибка сервера: " + std::string(e.what()), "text/plain");
        }
    });
}
