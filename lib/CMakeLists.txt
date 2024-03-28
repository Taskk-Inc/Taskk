cmake_minimum_required(VERSION 3.27)
project(lib)

set(CMAKE_CXX_STANDARD 17)

add_library(lib SHARED
        # api declarations
        include/taskk.h
        include/taskk.hpp
        include/taskk/c/taskk_api.h
        include/taskk/cxx/include_all.hpp
        include/taskk/cxx/data_types/data_types.hpp
        include/taskk/cxx/macros/make_scope_operation.hpp
        include/taskk/cxx/macros/taskk_api.hpp
        include/taskk/cxx/macros/utils.hpp
        # api definitions
        src/taskk/c_api.cpp
        src/taskk/cxx_wrapper.cpp
        src/taskk/cxx/data_types.cpp
        # logic
        src/logic/logic.cpp
        src/logic/logic.hpp
        # data types
        src/data_types/data_types.hpp
        # globals
        src/globals/globals.hpp
        # utils
        src/utils/utils.cpp
        src/utils/utils.hpp
        # i/o
        src/io/io.cpp
        src/io/io.hpp
        #json
        src/json/json.cpp
        src/json/json.hpp
        #macros
        src/macros/custom_types.hpp
        src/macros/functions.hpp
)

set_target_properties(lib PROPERTIES PREFIX "" OUTPUT_NAME "taskk")


target_link_libraries(lib PRIVATE ${PROJECT_SOURCE_DIR}/libs/jansson/bin/libjansson.a)

target_include_directories(lib PRIVATE
        .
        include
        src
        libs/jansson/include)

target_compile_definitions(lib PRIVATE TASKK_EXPORT)
