cmake_minimum_required(VERSION 3.1)
project(university_tasks)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(HEADERS GeometricFigures.h)
set(SOURCE_FILES Intersections/src/main.cpp Intersections/src/GeometricFigures.cpp)
add_executable(main Intersections/src/main.cpp Intersections/src/GeometricFigures.cpp)