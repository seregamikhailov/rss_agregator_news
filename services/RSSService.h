#pragma once
#include <string>
#include <vector>
#include "INewsService.h"
#include <RSSFetcher.h>

class RSSService: public INewsService{
public:
    std::vector<XMLItem> getFilteredNews(const std::string &source, const std::string &keywords,int limit) override;
};
