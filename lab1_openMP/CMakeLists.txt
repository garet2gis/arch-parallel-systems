cmake_minimum_required(VERSION 3.6)
project(lab1_openMP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILES main.cpp)
add_executable(lab1_openMP main.cpp)
