#include "CurlWrapper.h"
#include <curl/curl.h>

size_t writeCallback(void *contents, size_t size, size_t nmemb, std::string *userdata) {
    size_t totalSize = size * nmemb;
    userdata->append((char *) contents, totalSize);
    return totalSize;
}

std::string CurlWrapper::fetchData(const std::string &url) {
    std::string data;
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return data;
}
