add_library(${LIBRARY_NAME} STATIC Board.hpp Cell.hpp GameOfLife.hpp GameOfLifeExporter.hpp GameOfLifeLoader.hpp GameOfLifeService.hpp PlayingBoard.cpp PlayingBoardMemento.hpp)
target_include_directories(${LIBRARY_NAME} PUBLIC "./")
