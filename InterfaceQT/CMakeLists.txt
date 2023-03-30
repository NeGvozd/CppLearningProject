cmake_minimum_required(VERSION 3.5)

project(Zrk_Interface LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



find_package(Qt5 COMPONENTS Widgets Sql REQUIRED)


add_executable(Zrk_Interface
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    object.cpp
    object.h
    database.cpp
    database.h
)

target_link_libraries(Zrk_Interface PRIVATE Qt5::Widgets Qt5::Sql)
