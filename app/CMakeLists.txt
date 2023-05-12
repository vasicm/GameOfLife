add_executable(${EXECUTABLE_NAME} main.cpp GameOfLifeService.hpp)

target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${LIBRARY_NAME})

#target_link_libraries(${EXECUTABLE_NAME}  PRIVATE PNGwriter::PNGwriter)
