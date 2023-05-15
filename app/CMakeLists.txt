add_executable(${EXECUTABLE_NAME} main.cpp StdUserInterface.hpp GameOfLifeService.hpp )

target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${LIBRARY_NAME})
