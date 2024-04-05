cmake_minimum_required(VERSION 3.27)
project(taskk)
enable_testing()

include(cmake/macros.cmake)

add_subdirectory("client")
add_subdirectory("lib")
add_subdirectory("example")
message_separator()