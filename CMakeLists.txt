cmake_minimum_required(VERSION 3.29)
project(rss_agregator_rss)

set(CMAKE_CXX_STANDARD 26)

include_directories(third_party/tinyxml2 third_party/cpp-httplib third_party/json)


add_executable(rss_agregator_rss main.cpp
        XMLItem/XMLItem.h
        XMLItem/XMLItem.cpp
        third_party/tinyxml2/tinyxml2.cpp)
find_package(CURL REQUIRED)

if (WIN32)
    target_link_libraries(rss_agregator_rss PRIVATE CURL::libcurl ws2_32)
else ()
    target_link_libraries(rss_agregator_rss PRIVATE CURL::libcurl)
endif ()
