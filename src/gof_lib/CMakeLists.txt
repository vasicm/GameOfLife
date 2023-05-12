add_library(${LIBRARY_NAME} STATIC Board.cpp Cell.hpp GameOfLife.cpp GameOfLifeExporter.hpp GameOfLifeLoader.hpp PlayingBoard.cpp PlayingBoardMemento.hpp)
target_include_directories(${LIBRARY_NAME} PUBLIC "./")

target_link_libraries(${LIBRARY_NAME} PUBLIC
    spdlog::spdlog
    PNGwriter
    )

#target_link_libraries(${LIBRARY_NAME}  PRIVATE pngwriter::pngwriter)
