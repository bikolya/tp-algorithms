cmake_minimum_required(VERSION 2.8.4)
project(3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES 3_3.cpp)
add_executable(3 ${SOURCE_FILES})