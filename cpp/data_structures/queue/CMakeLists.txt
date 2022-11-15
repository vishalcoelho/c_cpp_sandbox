cmake_minimum_required(VERSION 2.4)
project(queue)
set(SOURCES queue.hpp queue.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})