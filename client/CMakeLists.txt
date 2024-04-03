cmake_minimum_required(VERSION 3.27)
project(client)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/QT/6.6.2/mingw_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        REQUIRED)

add_executable(client src/main.cpp
        src/ui/ui.cpp
        src/ui/ui.hpp
        src/templates/delegate.hpp
        src/ui/ui_creation_helpers.hpp
        src/ui/ui_mainwindow.h
        src/ui/mainwindow.h
        src/ui/mainwindow.cpp
        src/ui/mainwindow.ui
        src/Handlers/OperationsBarData/OperationsBarData.h
        src/Handlers/OperationsBarData/OperationsBarData.cpp
        src/ui/QTClasses/PDataScrollBar.hpp
        src/ui/QTClasses/PDataScrollBar.hpp
        src/Handlers/DataHandler/DataHandler.hpp
        src/Handlers/DataHandler/DataHandler.hpp
        Resources/icon.rc
        src/ui/Widgets/TimelineWidget.hpp
        src/ui/Widgets/MenuBar.hpp
)

target_include_directories(client PRIVATE
        src
        src/ui
        libs/ads/include
        libs/jansson/include)


include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(client
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Charts
        ${PROJECT_SOURCE_DIR}/libs/jansson/bin/libjansson.a
        ${PROJECT_SOURCE_DIR}/libs/ads/bin/libqtadvanceddocking.a
        nlohmann_json::nlohmann_json
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
