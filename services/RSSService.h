#pragma once
#include <string>
#include <vector>

#include "XMLItem/XMLItem.h"

class RSSService {
public:
    std::vector<XMLItem> getFilteredNews(const std::string &source, const std::string &keywords);
};
