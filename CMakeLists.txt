cmake_minimum_required(VERSION 3.13)

project(postupashki-course)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(Catch2 3 REQUIRED)

include(cmake/Utils.cmake)

include_directories(utils)

# include_catch2()

add_subdirectory(tasks)
