set(TEST_MAIN "unit_tests")
set(TEST_SOURCES "main.cpp" "board_test.cpp" "game_of_life_test.cpp")

add_executable(${TEST_MAIN} ${TEST_SOURCES})
target_link_libraries(${TEST_MAIN}  ${LIBRARY_NAME} gtest_main gmock_main)
