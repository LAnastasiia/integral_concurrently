cmake_minimum_required(VERSION 3.5)
project(integral_concurrently)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)

add_executable(integral_concurrently main.cpp additional.cpp time_measure.h integrate.cpp config.cpp)
add_executable(test_integral_concurrently compare_script.cpp additional.cpp time_measure.h integrate.cpp config.cpp)

target_link_libraries(integral_concurrently Threads::Threads)
target_link_libraries(test_integral_concurrently Threads::Threads)
