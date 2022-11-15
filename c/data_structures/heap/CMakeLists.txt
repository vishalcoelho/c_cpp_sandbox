cmake_minimum_required(VERSION 2.4)
project(heap)

set(HEAP_ROOT_DIR ..)

# add_compile_definitions(DEBUG=1)

set(HEADERS heap.h ${HEAP_ROOT_DIR}/utils/utils.h)
set(SOURCES heap.c)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${HEAP_ROOT_DIR})
