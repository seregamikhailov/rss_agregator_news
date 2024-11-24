#include <iostream>
#include <string>
#include <httplib.h>
#include <tinyxml2.h>
#include <json.hpp>
#include <vector>
#include "XMLItem/XMLItem.h"
#include <curl/curl.h>
using namespace std;
using json = nlohmann::json;

const string RSSFONTANKA = "https://www.fontanka.ru/rss-feeds/rss.xml";

vector<XMLItem> fetchRSS(const string &url);

size_t write_callback(void *contents, size_t size, size_t nmemb, string *userdata);

int main() {
    system("chcp 65001");
    vector<XMLItem> rssVector = fetchRSS(RSSFONTANKA);
    for (int i = 0; i < rssVector.size(); i++) {
        rssVector[i].print_item();
    }
    return 0;
}

size_t write_callback(void *contents, size_t size, size_t nmemb, string *userdata) {
    size_t totalSize = size * nmemb;
    userdata->append((char *) contents, totalSize);
    return totalSize;
}

vector<XMLItem> fetchRSS(const string &url) {
    vector<XMLItem> items;
    CURL *curl = curl_easy_init();
    if (curl) {
        string rssData;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rssData);
        CURLcode response = curl_easy_perform(curl);

        if (response == CURLE_OK) {
            tinyxml2::XMLDocument doc;
            if (doc.Parse(rssData.c_str()) == tinyxml2::XML_SUCCESS) {
                tinyxml2::XMLElement *channel = doc.FirstChildElement("rss")->FirstChildElement("channel");
                tinyxml2::XMLElement *item = channel->FirstChildElement("item");
                while (item) {
                    const char *title = item->FirstChildElement("title")->GetText();
                    const char *link = item->FirstChildElement("link")->GetText();
                    const char *category = item->FirstChildElement("category")
                                               ? item->FirstChildElement("category")->GetText()
                                               : "No category";
                    items.emplace_back(title ? title : "", link ? link : "", category);
                    item = item->NextSiblingElement("item");
                }
            } else {
                cerr << "Не удалось распарсить RSS данные\n";
            }
        } else {
            cerr << "Ошибка ответа CURL: " << curl_easy_strerror(response) << "\n";
        }
        curl_easy_cleanup(curl);
    } else {
        cerr << "Не удалось инициализировать CURL\n";
    }
    return items;
}
