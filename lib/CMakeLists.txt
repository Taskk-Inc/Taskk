cmake_minimum_required(VERSION 3.27)
project(lib)

set(CMAKE_CXX_STANDARD 17)

add_library(lib SHARED src/taskk.cpp
        src/include/taskk/taskk.h
        src/include/taskk/taskk_api.h
        src/include/taskk/taskk.hpp
        src/include/taskk/taskk_api.hpp
        src/taskk_cxx_wrapper.cpp
        src/logic/logic.cpp
        src/logic/logic.hpp
        src/data_types/data_types.hpp
        src/globals/globals.hpp
        src/utils/utils.cpp
        src/utils/utils.hpp
        src/globals/globals.cpp
        src/io/io.cpp
        src/io/io.hpp
        src/json/json.cpp
        src/json/json.hpp)

set_target_properties(lib PROPERTIES PREFIX "" OUTPUT_NAME "taskk")


target_link_libraries(lib PRIVATE ${PROJECT_SOURCE_DIR}/libs/jansson/bin/libjansson.a)

target_include_directories(lib PRIVATE
        src
        libs/jansson/include)

target_compile_definitions(lib PRIVATE TASKK_EXPORT)
