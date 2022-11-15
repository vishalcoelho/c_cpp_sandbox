cmake_minimum_required(VERSION 2.4)

# This doenst do anything
# SET(CMAKE_C_COMPILER "/c/qp/qtools/mingw32/bin/gcc")
# SET(CMAKE_CXX_COMPILER "/c/qp/qtools/mingw32/bin/gcc")

project(Timer)

set(HEADERS Timer.h)
set(SOURCE main.c Timer.c)

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})