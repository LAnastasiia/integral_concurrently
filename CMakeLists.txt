cmake_minimum_required(VERSION 3.14)
project(integral_concurrently)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

add_executable(integral_concurrently main.cpp config.h additional.cpp time_measure.h)

target_link_libraries(integral_concurrently Threads::Threads)
