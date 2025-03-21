cmake_minimum_required(VERSION 3.10)

# Cmake tries to compile a simple executable using "standard" options to see
# if the compiler works. Sometimes, especially when cross-compiling, you dont
# want to link against the x86 std C library, so you can instruct cmake to just
# test compile a static library instead.
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# NOTE: Uncomment if you want to force a particular toolchain
# If you set the compiler you circumvent cmake's auto-tool detection process which
# may not be a good thing in a multi build environment. I am overriding (FORCE) what
# is in CMake's cache as well.
# set(CMAKE_C_COMPILER "/c/msys64/ucrt64/bin/gcc" CACHE PATH "" FORCE)
# set(CMAKE_CXX_COMPILER "/c/msys64/ucrt64/bin/g++" CACHE PATH "" FORCE)
# set(CMAKE_MAKE_PROGRAM "/c/msys64/ucrt64/bin/mingw32-make" CACHE PATH "" FORCE)

project(subclassing_with_queue)

set(SUBCLASSING_ROOT_DIR ..)
# add_compile_definitions(DEBUG=1)

# Cache variable that is set at the command line
set(BUILD_BASE_CLASS_TEST False CACHE BOOL "Build the base class test")

# Invoke CMake with -DBUILD_QUEUE to build just the base class and test
if (${BUILD_BASE_CLASS_TEST})
    message(STATUS "Building base queue class and its test")
    set(HEADERS queue.h)
    set(SOURCES queue.c test_queue.c)
else()
    message(STATUS "Building derived cached queue class and its test")
    set(HEADERS queue.h cached_queue.h)
    set(SOURCES queue.c cached_queue.c test_cached_queue.c)
endif()

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${SUBCLASSING_ROOT_DIR})
