add_executable(${EXECUTABLE_NAME} main.cpp user_interface/StdUserInterface.hpp TheGame.hpp )

target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${LIBRARY_NAME})
