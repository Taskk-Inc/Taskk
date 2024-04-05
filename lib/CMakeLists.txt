cmake_minimum_required(VERSION 3.27)
project(lib)

message_separator()
message("Taskk : Generating the library")
message_small_separator()

# if it wasn't for 'using enum' c++20 wouldn't be required, it shouldn't be that hard to backport
set(CMAKE_CXX_STANDARD 20)

include_directories(. include src libs/jansson/include)
link_libraries(${PROJECT_SOURCE_DIR}/libs/jansson/bin/libjansson.a)
include(cmake/source_lists.cmake)

add_library(lib SHARED ${LIB_API_SOURCES} ${LIB_SOURCES})
set_target_properties(lib PROPERTIES PREFIX "" OUTPUT_NAME "taskk")
target_compile_definitions(lib PRIVATE TASKK_EXPORT)

# unit testing
option(TASKK_LIB_BUILD_TESTS "Build unit tests for the taskk library." OFF)
if(TASKK_LIB_BUILD_TESTS STREQUAL ON)
    message("Generating Unit Tests")
    include(tests/tests.cmake)
else()
    message("Taskk : Unit tests for the Taskk library will *not* be built.\nConsider enabling them with TASKK_LIB_BUILD_TESTS")
endif()

message("Taskk library generation done")
