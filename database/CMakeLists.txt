cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME database)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_library(database ${SOURCES})

target_include_directories(database PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(database
    Qt5::Core
    Qt5::Widgets
    Qt5::Sql)

#add_executable(${PROJECT_NAME} ${source_list})
