cmake_minimum_required(VERSION 3.0.0)

project(MtmEx3)

set(CMAKE_TEST_DEBUG "-pedantic-errors -Wall -Werror")
set(CMAKE_TEST_RELEASE "${CMAKE_TEST_DEBUG} -DNDEBUG")

set(CMAKE_C_FLAGS ${CMAKE_TEST_DEBUG})

add_library(IntMatrix partA/IntMatrix.cpp partA/Auxiliaries.cpp partA/test_partA.cpp)
add_library(Matrix partB/Matrix.cpp partB/Auxiliaries.cpp)
add_library(Game partC/Medic.cpp partC/Character.cpp partC/Sniper.cpp partC/Soldier.cpp)