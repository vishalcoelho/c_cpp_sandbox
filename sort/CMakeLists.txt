cmake_minimum_required(VERSION 2.4)
project(sort)

set(SORT_ROOT_DIR ..)

set(HEADERS simple.hpp selection.hpp bubble.hpp insertion.hpp merge.hpp utils.hpp common.h)
set(SOURCES sort.cpp)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${SORT_ROOT_DIR})

# Link the 'common' folder to the executable as well as the common library
target_link_directories(${PROJECT_NAME} PRIVATE ${SORT_ROOT_DIR})