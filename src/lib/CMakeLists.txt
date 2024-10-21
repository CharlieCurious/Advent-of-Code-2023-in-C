cmake_minimum_required(VERSION 3.22.1)

project(lib)

option(ENABLE_TESTING "Include tests in compilation." ON)

if(ENABLE_TESTING)
    set(UNITY_PATH ../../dependencies/unity)
    add_subdirectory(${UNITY_PATH} ${CMAKE_BINARY_DIR}/dependencies/unity)
    enable_testing()
    add_subdirectory(tests)
endif()

add_library(lib lib.c)

target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})