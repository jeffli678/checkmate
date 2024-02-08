cmake_minimum_required(VERSION 3.23)

project(checkmate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

add_executable(checkmate
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/engine.h
    src/engine.cpp
    src/boardposition.h
    src/boardposition.cpp
)

target_link_libraries(checkmate PRIVATE Qt6::Widgets)

set_target_properties(checkmate PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
