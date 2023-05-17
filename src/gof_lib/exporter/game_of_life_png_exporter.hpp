#pragma once

#include <pngwriter.h>

#include <string>

#include "game_of_life.hpp"

// Used to export a 'board' object to a png file
class GameOfLifePngExporter {
 public:

  // Exports board to PNG file.
  // Input:
  //    board - Reference to a board object that needs to be exported
  //    png_location_path - a location where the board would be exported
  //    cell_size - the size of every cell in pixels
  static void ExportState(const std::shared_ptr<Board>& board, std::string png_location_path, int cell_size);
};
