set(TEST_MAIN "unit_tests")
set(TEST_SOURCES "main.cpp" "BoardTest.cpp" "GameOfLifeTest.cpp")

add_executable(${TEST_MAIN} ${TEST_SOURCES})
target_link_libraries(${TEST_MAIN}  ${LIBRARY_NAME} gtest_main gmock_main)
