cmake_minimum_required(VERSION 3.14)
project(integral_concurrently)

set(CMAKE_CXX_STANDARD 17)

add_executable(integral_concurrently main.cpp additional.cpp config.h time_measure.h time_measure.cpp compare_script.cpp)