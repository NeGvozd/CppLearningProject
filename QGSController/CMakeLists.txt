cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME QGSController)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QGIS_PATH /usr/local)

if(NOT DEFINED ENV{QGIS_PATH})
    set(QGIS_PATH /apps CACHE PATH "specify path to QGIS install directory")
endif()
message("QGIS_PATH is defined -- ${QGIS_PATH}")

find_package(Qt5 COMPONENTS Core Gui Widgets Xml)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

link_directories(/usr/lib)
link_directories(${QGIS_PATH}/lib)

add_library(QGSController ${SOURCES})

target_include_directories(QGSController PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src" ${QGIS_PATH}/include/qgis /usr/include/gdal)

target_link_directories(Zrk_Interface PRIVATE ${QGIS_PATH}/lib)

target_link_libraries(QGSController Qt5::Core Qt5::Xml Qt5::Gui Qt5::Widgets qgis_native qgis_core qgis_app qgis_gui gdal)

#add_executable(${PROJECT_NAME} ${source_list})