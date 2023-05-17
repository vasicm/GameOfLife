#include "game_of_life_png_exporter.hpp"

struct GameOfLifePngExporter::Color {
    int red;
    int green;
    int blue;
};

const GameOfLifePngExporter::Color GameOfLifePngExporter::kAliveCell{65535 / 3, 65535 / 2, 65535};
const GameOfLifePngExporter::Color GameOfLifePngExporter::kDeadCell{65535, 65535 / 2, 65535 / 3};

struct GameOfLifePngExporter::Position {
    int x;
    int y;
};

void GameOfLifePngExporter::RenderCell(pngwriter& flag, const Position& cell_position, const Color& color, int cell_size, int cell_margine_size) {
    flag.filledsquare(
                    cell_position.x,
                    cell_position.y,
                    cell_position.x + cell_size - cell_margine_size,
                    cell_position.y + cell_size - cell_margine_size,
                    color.red, color.green, color.blue);
}

void GameOfLifePngExporter::ExportState(
    const std::shared_ptr<Board>& board,
    std::string filepath,
    int cellsize) {

  // Calculates the resolution of the png file.
  // The resolution depends on the number of rows and columns as well as the size of one cell.
  int width = cellsize * board->GetWidth();
  int height = cellsize * board->GetHeight();

  // Generate the flag
  pngwriter flag{width, height, 0, filepath.data()};
  for (size_t i = 0; i < board->GetHeight(); i++) {
    for (size_t j = 0; j < board->GetWidth(); j++) {
      auto cell = (*board)[{i, j}];

      int positionX = j * cellsize;
      int positionY = i * cellsize;
      Position cellPosition{positionX, positionY};

      if (cell == Cell::kAlive) {
        RenderCell(flag, cellPosition, kAliveCell, cellsize);
      } else {
        RenderCell(flag, cellPosition, kDeadCell, cellsize);
      }
    }
  }

  // Close the flag
  flag.close();
}
