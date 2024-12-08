#ifndef NEWSCONTROLLER_H
#define NEWSCONTROLLER_H
#include <httplib.h>

#include "NewsService.h"
class NewsController {
public:
    void setupRoutes(httplib::Server &server, NewsService &newsService);
};


#endif //NEWSCONTROLLER_H
