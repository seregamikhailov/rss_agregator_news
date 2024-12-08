#pragma once
#include <string>
#include <vector>
#include "NewsService.h"
#include <RSSFetcher.h>

class RSSService: public NewsService{
public:
    std::vector<XMLItem> getFilteredNews(const std::string &source, const std::string &keywords,int limit) override;
};
