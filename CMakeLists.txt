cmake_minimum_required(VERSION 3.3)

set(PROJECT_NAME math_cpp)

project(${PROJECT_NAME})

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(${PROJECT_NAME} STATIC source/matrix.cpp source/vector2.cpp source/vector3.cpp source/trigonometry.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)