cmake_minimum_required(VERSION 2.8.4)
project(1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES 1_3.cpp)
add_executable(1 ${SOURCE_FILES})