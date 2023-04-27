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


add_executable(Zrk_Interface
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
#    QGSController.cpp
#    QGSController.h
    database.cpp
    database.h
    databasecontroller.cpp
    databasecontroller.h
    datawindow.cpp
    datawindow.h
    datawindow.ui
    objects/ObjectFactory.h
    objects/ObjectFactory.cpp
    objects/plane.h
    objects/plane.cpp
    objects/point.h
    objects/point.cpp
    objects/rocket.h
    objects/rocket.cpp
    objects/sam.h
    objects/sam.cpp
    resource.qrc
  )


target_include_directories(Zrk_Interface PRIVATE
                                    ${QGIS_PATH}/include/qgis
                                    /usr/include/gdal)

add_custom_command(TARGET Zrk_Interface POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/database/tth.db $<TARGET_FILE_DIR:Zrk_Interface>/tth.db)

target_link_directories(Zrk_Interface PRIVATE ${QGIS_PATH}/lib)
target_link_libraries(Zrk_Interface
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Xml
        Qt5::Sql
#        qgis_native
#        qgis_core
#        qgis_app
#        qgis_gui
#        gdal
        )

