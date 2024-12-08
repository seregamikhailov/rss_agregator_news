#pragma once
#include <string>

class CurlWrapper {
public:
    std::string fetchData(const std::string& url);
};
