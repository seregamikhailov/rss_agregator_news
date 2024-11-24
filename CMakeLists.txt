cmake_minimum_required(VERSION 3.29)
project(news_argegator_rss)

set(CMAKE_CXX_STANDARD 26)

include_directories(third_party/tinyxml2 third_party/cpp-httplib third_party/json)


add_executable(news_argegator_rss main.cpp
        XMLItem/XMLItem.h
        XMLItem/XMLItem.cpp
        third_party/tinyxml2/tinyxml2.cpp)
find_package(CURL REQUIRED)

target_link_libraries(news_argegator_rss PRIVATE CURL::libcurl ws2_32)