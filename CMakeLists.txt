cmake_minimum_required(VERSION 3.0.0)

project(MtmEx3)

set(CMAKE_TEST_DEBUG "-std=c++11 -pedantic-errors -Wall -Werror")
set(CMAKE_TEST_RELEASE "${CMAKE_TEST_DEBUG} -DNDEBUG")

set(CMAKE_C_FLAGS ${CMAKE_TEST_DEBUG})

add_library(IntMatrix partA/IntMatrix.cpp partA/Auxiliaries.cpp)
add_executable(Matrix partB/Auxiliaries.cpp partB/test_partB.cpp)
