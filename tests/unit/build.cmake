add_executable(test_1 ${CMAKE_CURRENT_LIST_DIR}/test_1.c)
target_link_libraries(test_1 PRIVATE traits-unit)
add_test(test_1 test_1)

add_executable(test_2 ${CMAKE_CURRENT_LIST_DIR}/test_2.c)
target_link_libraries(test_2 PRIVATE traits-unit)
add_test(test_2 test_2)

add_executable(test_3 ${CMAKE_CURRENT_LIST_DIR}/test_3.c)
target_link_libraries(test_3 PRIVATE traits-unit)
add_test(test_3 test_3)

add_executable(test_4 ${CMAKE_CURRENT_LIST_DIR}/test_4.c)
target_link_libraries(test_4 PRIVATE traits-unit)
add_test(test_4 test_4)

enable_testing()
