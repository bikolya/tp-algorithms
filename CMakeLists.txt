cmake_minimum_required(VERSION 2.8.4)
project(tp_algorithms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES tp-algorithms-1/1.cpp)
add_executable(tp_algorithms ${SOURCE_FILES})