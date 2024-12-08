#include "RSSService.h"
#include <RSSFetcher.h>
#include <sstream>
// добавить фильтр по категориям
// сортировка по дате  (старые или новые (новости за данные))
//
std::vector<XMLItem> RSSService::getFilteredNews(const std::string &source, const std::string &keywords, int limit) {
    RSSFetcher fetcher;
    std::vector<XMLItem> items = fetcher.fetch(source);

    if (!keywords.empty()) {
        std::vector<std::string> keywordList;
        std::istringstream ss(keywords);
        std::string keyword;
        while (std::getline(ss, keyword, ',')) {
            keywordList.push_back(keyword);
        }
        items = fetcher.filterByKeywords(items, keywordList);
    }
    if (limit > 0 && limit < items.size()) {
        items.resize(limit);
    }
    return items;
}
