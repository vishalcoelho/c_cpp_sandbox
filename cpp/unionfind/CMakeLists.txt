cmake_minimum_required(VERSION 2.4)
project(unionfind)
set(SOURCES unionfind.hpp unionfind.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})