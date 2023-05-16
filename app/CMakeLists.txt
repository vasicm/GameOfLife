add_executable(${EXECUTABLE_NAME} main.cpp user_interface/std_user_interface.cpp game.cpp game_of_life_factory.cpp )

target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${LIBRARY_NAME})
