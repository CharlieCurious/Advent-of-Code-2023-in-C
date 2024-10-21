add_executable(test_lib test_lib.c)

target_link_libraries(test_lib unity lib)

include(CTest)

add_test(NAME test_lib COMMAND test_lib)