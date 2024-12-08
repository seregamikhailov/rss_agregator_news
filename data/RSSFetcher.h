#pragma once
#include <vector>
#include <string>
#include "XMLItem/XMLItem.h"

class RSSFetcher {
public:
    std::vector<XMLItem> fetch(const std::string& url);
    std::vector<XMLItem> filterByKeywords(const std::vector<XMLItem>& items, const std::vector<std::string>& keywordList);
};
