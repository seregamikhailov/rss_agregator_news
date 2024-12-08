#include <iostream>
#include <httplib.h>
#include "controllers/NewsController.h"
#include "RSSService.h"

int main() {
    httplib::Server server;
    RSSService rssService;

    NewsController controller;
    controller.setupRoutes(server, rssService);
    std::cout << "Сервер запущен на http://localhost:8080/news\n";
    server.listen("0.0.0.0", 8080);
    return 0;
}
