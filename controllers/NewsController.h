#ifndef NEWSCONTROLLER_H
#define NEWSCONTROLLER_H
#include <httplib.h>


class NewsController {
public:
    void setupRoutes(httplib::Server &server);
};


#endif //NEWSCONTROLLER_H
