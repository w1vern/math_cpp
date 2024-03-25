cmake_minimum_required(VERSION 3.3)

project(math_cpp)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(math_lib STATIC source/matrix.cpp source/vector2.cpp source/vector3.cpp)