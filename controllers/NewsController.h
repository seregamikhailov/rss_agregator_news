#ifndef NEWSCONTROLLER_H
#define NEWSCONTROLLER_H
#include <httplib.h>

#include "INewsService.h"
class NewsController {
public:
    void setupRoutes(httplib::Server &server, INewsService &newsService);
};


#endif //NEWSCONTROLLER_H
