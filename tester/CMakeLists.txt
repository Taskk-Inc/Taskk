project(tester)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

add_executable(tester src/main.cpp)

target_include_directories(tester PRIVATE src ${PROJECT_SOURCE_DIR}/libs/taskk/include)

target_link_libraries(tester PRIVATE ${PROJECT_SOURCE_DIR}/libs/taskk/bin/taskk.dll.a)