cmake_minimum_required(VERSION 3.5)

project(Zrk_Interface LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QGIS_PATH /apps)

if(NOT DEFINED ENV{QGIS_PATH})
    set(QGIS_PATH /apps CACHE PATH "specify path to QGIS install directory")
endif()
message("QGIS_PATH is defined -- ${QGIS_PATH}")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Xml
        Sql
        REQUIRED)

link_directories(/usr/lib)
link_directories(${QGIS_PATH}/lib)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(Zrk_Interface SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(Zrk_Interface
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    QGSController.cpp
    QGSController.h
    resource.qrc
  )
endif()

target_include_directories(Zrk_Interface PRIVATE
                                    ${QGIS_PATH}/include/qgis
                                    /usr/include/gdal)

target_link_directories(Zrk_Interface PRIVATE ${QGIS_PATH}/lib)
target_link_libraries(Zrk_Interface
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Xml
        Qt5::Sql
        qgis_native
        qgis_core
        qgis_app
        qgis_gui
        gdal
        )