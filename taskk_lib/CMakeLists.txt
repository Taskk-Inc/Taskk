cmake_minimum_required(VERSION 3.27)
project(taskk_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(taskk_lib SHARED src/main.cpp)

target_include_directories(taskk_lib PRIVATE src)
