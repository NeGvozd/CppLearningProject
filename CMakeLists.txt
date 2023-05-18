cmake_minimum_required(VERSION 3.5)

project(Zrk_Interface LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        REQUIRED)


add_executable(Zrk_Interface
    datawindow.h
    mainwindow.h
    main.cpp
    mainwindow.cpp
    mainwindow.ui
    datawindow.cpp
    datawindow.ui
    itemslist.cpp
    itemslist.h
    ItemsListWindow.ui
    ItemsListWindow.cpp
    ItemsListWindow.h
    resource.qrc
  )

add_custom_command(TARGET Zrk_Interface POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/database/TECHNICALFEATURES.db $<TARGET_FILE_DIR:Zrk_Interface>/TECHNICALFEATURES.db)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/jsonData)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/objects)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/QGSController)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/database)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Engine)

include_directories(${Qt5_INCLUDE_DIR})

target_include_directories(Zrk_Interface PRIVATE
                                    QGSController/src
                                    Enigine/src
                                    database/src)

target_link_libraries(Zrk_Interface
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        QGSController
        Engine
        database
        )
