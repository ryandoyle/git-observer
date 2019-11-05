cmake_minimum_required(VERSION 3.15)
project(git_observer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(gito main.cpp application.qrc MainWindow.cpp MainWindow.h  GitLogWidget.cpp GitLogWidget.h)

target_link_libraries(gito Qt5::Widgets git2)
