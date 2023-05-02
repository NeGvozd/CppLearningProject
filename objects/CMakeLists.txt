cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME objects)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_library(objects ${SOURCES})

target_include_directories(objects PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(objects Qt5::Core)

#add_executable(${PROJECT_NAME} ${source_list})