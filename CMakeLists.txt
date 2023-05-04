cmake_minimum_required(VERSION 3.5)

project(Zrk_Interface LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
#        Network
        REQUIRED)

link_directories(/usr/lib)
link_directories(${QGIS_PATH}/lib)

find_package(Qt5 COMPONENTS Widgets REQUIRED)


add_executable(Zrk_Interface
    database.h
    databasecontroller.h
    datawindow.h
#    QGSController.h
    mainwindow.h
    main.cpp
    mainwindow.cpp
    mainwindow.ui
#    QGSController.cpp
    database.cpp
    databasecontroller.cpp
    datawindow.cpp
    datawindow.ui
    chooseline.h
    chooseline.ui
    chooseline.cpp
    resource.qrc
  )

add_custom_command(TARGET Zrk_Interface POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/database/tth.db $<TARGET_FILE_DIR:Zrk_Interface>/tth.db)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/objects)

include_directories(${Qt5_INCLUDE_DIR})

target_include_directories(Zrk_Interface PRIVATE
                                    ${QGIS_PATH}/include/qgis
                                    /usr/include/gdal
                                    objects/src)

target_link_directories(Zrk_Interface PRIVATE ${QGIS_PATH}/lib)
target_link_libraries(Zrk_Interface
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Xml
        Qt5::Sql
#        Qt5::Network
#        qgis_native
#        qgis_core
#        qgis_app
#        qgis_gui
#        gdal
        objects
        )
