add_library(${LIBRARY_NAME} STATIC
core/Board.cpp core/Cell.hpp
GameOfLife.cpp
exporter/GameOfLifeFileExporter.hpp exporter/GameOfLifePngExporter.hpp
PlayingBoardMemento.hpp
loader/GameOfLifeFromFileLoader.hpp loader/RandomValuesGameOfLifeLoader.hpp)

target_include_directories(${LIBRARY_NAME} PUBLIC "./")

target_link_libraries(${LIBRARY_NAME} PUBLIC
    spdlog::spdlog
    PNGwriter
    )

#add_subdirectory(loader)
