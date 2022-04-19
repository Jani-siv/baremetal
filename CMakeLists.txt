
#cmake version
cmake_minimum_required(VERSION 3.18.4)
#cmake project
project(globalProject)
add_subdirectory(core)
add_subdirectory(tests)
#C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#include dir
include_directories(include)

#make executable
#add_executable(${PROJECT_NAME} ${SOURCES})

