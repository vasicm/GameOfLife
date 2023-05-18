#pragma once

#include <string>

#include "../core/board.hpp"

// Used to export a 'board' object to a txt file
class GameOfLifeFileExporter {
 public:

  // Exports board to a text file.
  // Input:
  //    board - Reference to a board object that needs to be exported
  //    initial_number_of_generations - Initial number of generations
  //    time_increment_in_ms - Time increment in milisecunds
  //    file_path - a location where the board would be exported
  static void ExportState(
    const std::shared_ptr<Board> &board,
    int initial_number_of_generations,
    int time_increment_in_ms,
    std::string file_path);

  static bool CheckIfFileExists(std::string file_path);
};
