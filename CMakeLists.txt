cmake_minimum_required(VERSION 3.29)
project(rss_agregator_rss)

set(CMAKE_CXX_STANDARD 26)

add_executable(rss_agregator_rss main.cpp
        XMLItem/XMLItem.h
        XMLItem/XMLItem.cpp)
