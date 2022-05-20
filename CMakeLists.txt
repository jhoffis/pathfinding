cmake_minimum_required(VERSION 3.22)
project(path)

set(CMAKE_CXX_STANDARD 20)

add_executable(path main.cpp junction_based.cpp point_based.cpp)
