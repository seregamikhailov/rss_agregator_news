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
const string RSSRIA = "https://ria.ru/export/rss2/archive/index.xml";
const string RSSE1 = "https://www.e1.ru/rss-feeds/rss.xml";

vector<XMLItem> fetchRSS(const string &url);

size_t write_callback(void *contents, size_t size, size_t nmemb, string *userdata);

int main() {
    system("chcp 65001");
    vector<XMLItem> rssVector = fetchRSS(RSSFONTANKA);
    httplib::Server svr;

    svr.Get("/news", [](const httplib::Request &req, httplib::Response &res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        try {
            string rssUrl = RSSFONTANKA;
            if (req.has_param("source")) {
                string source = req.get_param_value("source");
                if (source == "ria") {
                    rssUrl = RSSRIA;
                } else if (source == "e1") {
                    rssUrl = RSSE1;
                } else if (source != "fontanka") {
                    res.status = 400;
                    res.set_content("Неверный параметр source. Допустимые значения: fontanka, ria.", "text/plain");
                    return;
                }
            }

            vector<XMLItem> items = fetchRSS(rssUrl);
            json responseJson = json::array();

            for (const auto &item: items) {
                responseJson.push_back(item.toJson());
            }

            res.set_content(responseJson.dump(4), "application/json");
        } catch (const exception &e) {
            res.status = 500;
            res.set_content(string("Ошибка сервера: ") + e.what(), "text/plain");
        }
    });


    cout << "Сервер запущен на http://localhost:8080/news\n";
    svr.listen("0.0.0.0", 8080);

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
