cmake_minimum_required(VERSION 3.0)

project(NestingProgram)

set (CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "*.cpp" "*.h" "Utils/*.cpp" "Utils/*.h")

include_directories("../3rdparty")
include_directories("../NestingLib/include")

add_executable(${PROJECT_NAME} ${SOURCES} "main.cpp")
target_link_libraries(${PROJECT_NAME} NestingLib)


file(GLOB JOB_FILES "SampleJobs/*.json")
file(COPY ${JOB_FILES} DESTINATION ${CMAKE_BINARY_DIR}/NestingProgram)
