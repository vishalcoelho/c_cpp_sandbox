cmake_minimum_required(VERSION 2.4)
project(binarysearchtree)
set(SOURCES binarysearchtree.hpp binarysearchtree.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})