add_library(${LIBRARY_NAME} STATIC
core/board.cpp core/cell.hpp
game_of_life.cpp
exporter/game_of_life_file_exporter.cpp exporter/game_of_life_png_exporter.cpp
board_memento.cpp
loader/game_of_life_from_file_loader.cpp loader/random_values_game_of_life_loader.cpp)

target_include_directories(${LIBRARY_NAME} PUBLIC "./")

target_link_libraries(${LIBRARY_NAME} PUBLIC
    spdlog::spdlog
    PNGwriter
    )

#add_subdirectory(loader)
