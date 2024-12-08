#include <iostream>
#include <httplib.h>
#include "controllers/NewsController.h"

int main() {
    httplib::Server server;
    NewsController newsController;
    newsController.setupRoutes(server);
    std::cout << "Сервер запущен на http://localhost:8080/news\n";
    server.listen("0.0.0.0", 8080);
    return 0;
}
