cmake_minimum_required(VERSION 3.0)

project(NestingLib)

set (CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "Source/*.cpp" "Source/*.h" "include/Nesting/*.h")

include_directories("../3rdparty")
include_directories("include/Nesting")

add_library(${PROJECT_NAME} STATIC ${SOURCES})