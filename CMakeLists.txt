cmake_minimum_required(VERSION 3.0.0)

project(MtmEx3)

set(CMAKE_TEST_DEBUG "-std=c++11 -pedantic-errors -Wall -Werror")
set(CMAKE_TEST_RELEASE "${CMAKE_TEST_DEBUG} -DNDEBUG")

set(CMAKE_C_FLAGS ${CMAKE_TEST_DEBUG})

# add_executable(IntMatrix Auxiliaries.cpp test_partA.cpp)  # Using partB
# add_executable(IntMatrix partA/IntMatrix.cpp Auxiliaries.cpp test_partA.cpp)
add_executable(Matrix Auxiliaries.cpp test_partB.cpp)
add_executable(CSGO 
                partC/Game.cpp
                partC/Character.cpp
                partC/Sniper.cpp
                partC/Soldier.cpp
                partC/Medic.cpp
                Auxiliaries.cpp 
                test_partC.cpp)
