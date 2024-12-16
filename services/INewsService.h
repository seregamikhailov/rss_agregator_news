// INewsService.h
#ifndef NEWS_SERVICE_H
#define NEWS_SERVICE_H

#include <vector>
#include <string>
#include "XMLItem/XMLItem.h"

class INewsService {
public:
    virtual std::vector<XMLItem> getFilteredNews(const std::string &source, const std::string &keywords, int limit) = 0;
    virtual ~INewsService() = default;
};

#endif
