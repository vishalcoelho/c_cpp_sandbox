cmake_minimum_required(VERSION 2.4)
project(dynamicarray)
set(SOURCES dynamicarray.hpp dynamicarray.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})