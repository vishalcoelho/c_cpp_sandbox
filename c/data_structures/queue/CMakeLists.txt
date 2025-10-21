cmake_minimum_required(VERSION 3.10)
project(queue)

set(QUEUE_ROOT_DIR ..)

set(HEADERS queue.h)
set(SOURCES queue.c main.c)

add_compile_definitions(CMAKE_BUILD)
add_compile_definitions(DEBUG=1)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${QUEUE_ROOT_DIR})

# Link the 'common' folder to the executable as well as the common library
target_link_directories(${PROJECT_NAME} PRIVATE ${QUEUE_ROOT_DIR})