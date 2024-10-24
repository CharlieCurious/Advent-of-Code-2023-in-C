cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (Debug, Release)" FORCE)
endif()

project(day-01)

add_executable(main main.c)

add_subdirectory(../lib ${CMAKE_BINARY_DIR}/lib)

target_link_libraries(main PRIVATE lib)