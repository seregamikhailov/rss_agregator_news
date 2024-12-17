#include "RSSFetcher.h"
#include "CurlWrapper.h"
#include <tinyxml2.h>
#include <vector>

#include "XMLItem/XMLItem.h"
#include "ParseException.h"

std::vector<XMLItem> RSSFetcher::fetch(const std::string &url) {
    CurlWrapper curlWrapper;
    std::string rssData = curlWrapper.fetchData(url);
    std::vector<XMLItem> items;

    tinyxml2::XMLDocument doc;
    if (doc.Parse(rssData.c_str()) != tinyxml2::XML_SUCCESS) {
        throw ParseException("Ошибка разбора RSS-данных");
    }

    tinyxml2::XMLElement *channel = doc.FirstChildElement("rss")->FirstChildElement("channel");
    if (!channel) throw ParseException("Элемент channel не найден");
    auto *item = channel->FirstChildElement("item");
    while (item) {
        const char *title = item->FirstChildElement("title")->GetText();
        const char *link = item->FirstChildElement("link")->GetText();
        items.emplace_back(title ? title : "", link ? link : "");
        item = item->NextSiblingElement("item");
    }

    return items;
}

std::vector<XMLItem> RSSFetcher::filterByKeywords(const std::vector<XMLItem> &items,
                                                  const std::vector<std::string> &keywordList) {
    std::vector<XMLItem> filteredItems;
    for (const auto &item: items) {
        for (const auto &kw: keywordList) {
            if (item.getTitle().find(kw) != std::string::npos) {
                filteredItems.push_back(item);
                break;
            }
        }
    }
    return filteredItems;
}
