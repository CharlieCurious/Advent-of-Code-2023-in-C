cmake_minimum_required(VERSION 3.22.1)

project(day-01)

add_executable(main main.c)

add_subdirectory(../lib ${CMAKE_BINARY_DIR}/lib)

target_link_libraries(main PRIVATE lib)