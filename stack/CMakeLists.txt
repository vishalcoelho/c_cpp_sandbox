cmake_minimum_required(VERSION 2.4)
project(stack)
set(SOURCES stack.hpp stack.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})