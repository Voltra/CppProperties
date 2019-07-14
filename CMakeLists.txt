cmake_minimum_required(VERSION 3.14)
project(property)

set(CMAKE_CXX_STANDARD 11)

add_executable(property main.cpp)
target_include_directories(property PUBLIC include)