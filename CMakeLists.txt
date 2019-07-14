cmake_minimum_required(VERSION 3.14)
project(property)

set(CMAKE_CXX_STANDARD 11)

add_executable(property main.cpp include/properties/property.h include/properties/utils.h include/properties/readonly.h include/properties/Guarded.h)
target_include_directories(property PUBLIC include)