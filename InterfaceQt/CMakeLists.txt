cmake_minimum_required(VERSION 3.5)

project(Zrk_Interface LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QGIS_PATH /apps)

if(NOT DEFINED ENV{QGIS_PATH})
    set(QGIS_PATH /apps CACHE PATH "specify path to QGIS install directory")
endif()
message("QGIS_PATH is defined -- ${QGIS_PATH}")

find_package(Qt5 COMPONENTS Widgets Xml Sql Test REQUIRED)

link_directories(/usr/lib)
link_directories(${QGIS_PATH}/lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(Zrk_Interface
    main.cpp
    mainwindow.cpp
    mainwindow.h
    object.cpp
    object.h
    database.cpp
    database.h
#    databasecontroller.cpp
#    databasecontroller.h
    mainwindow.ui
    resource.qrc
    mapwindow.cpp
    mapwindow.h
)

target_include_directories(Zrk_Interface PRIVATE
                                    ${QGIS_PATH}/include/qgis
                                    /usr/include/gdal)

target_link_directories(Zrk_Interface PRIVATE ${QGIS_PATH}/lib)

target_link_libraries(Zrk_Interface PRIVATE Qt5::Widgets Qt5::Xml Qt5::Sql Qt5::Test qgis_native qgis_core qgis_app qgis_gui gdal)
