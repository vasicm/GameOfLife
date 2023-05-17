#pragma once

#include <pngwriter.h>

#include <string>

#include "game_of_life.hpp"

#define DEFAULT_MARGINE_SIZE 2

// Used to export a 'board' object to a png file
class GameOfLifePngExporter {
 private:
    struct Color;
    struct Position;
    static const Color kAliveCell;
    static const Color kDeadCell;

    // Renders one cell of the board.
    static void RenderCell(pngwriter& flag, const Position& cell_position, const Color& color, int cell_size, int cell_margine_size = DEFAULT_MARGINE_SIZE);
 public:

  // Exports board to PNG file.
  // Input:
  //    board - Reference to a board object that needs to be exported
  //    png_location_path - a location where the board would be exported
  //    cell_size - the size of every cell in pixels
  static void ExportState(const std::shared_ptr<Board>& board, std::string png_location_path, int cell_size);
};
