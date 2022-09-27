cmake_minimum_required(VERSION 3.23)
project(lab2_mpi)

include_directories(/opt/homebrew/include/mpi/)
set(CMAKE_C_COMPILER "/opt/homebrew/bin/mpicc")
set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/mpic++")

add_executable(lab2_mpi main.cpp)
