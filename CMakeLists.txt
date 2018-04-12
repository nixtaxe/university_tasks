cmake_minimum_required(VERSION 3.1)
project(university_tasks)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(HEADERS GeometricFigures.h)
set(SOURCE_FILES Intersections/src/main.cpp Intersections/src/GeometricFigures.cpp)
add_executable(main ${SOURCE_FILES})


target_compile_options(main PRIVATE -g3 -O0 -coverage)
set_target_properties(main PROPERTIES LINK_FLAGS "${LINK_FLAGS} -coverage")