cmake_minimum_required(VERSION 2.4)
project(binaryheap)
set(SOURCES binaryheap.hpp binaryheap.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})