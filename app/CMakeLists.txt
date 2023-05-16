add_executable(${EXECUTABLE_NAME} main.cpp user_interface/std_user_interface.hpp game.hpp )

target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${LIBRARY_NAME})
