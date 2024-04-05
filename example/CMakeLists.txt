project(example)

message("Generating the Taskk example project")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

add_executable(example src/main.cpp
        src/main.c
        src/switch.h)

target_include_directories(example PRIVATE src ${PROJECT_SOURCE_DIR}/libs/taskk/include)

target_link_libraries(example PRIVATE ${PROJECT_SOURCE_DIR}/libs/taskk/bin/taskk.dll.a)