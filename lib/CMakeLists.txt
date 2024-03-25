cmake_minimum_required(VERSION 3.27)
project(lib)

set(CMAKE_CXX_STANDARD 17)

add_library(lib SHARED src/taskk.cpp
        src/include/taskk/taskk.h
        src/include/taskk/taskk_api.h)

set_target_properties(lib PROPERTIES PREFIX "" OUTPUT_NAME "taskk")

target_include_directories(lib PRIVATE src)

target_compile_definitions(lib PRIVATE TASKK_EXPORT)
