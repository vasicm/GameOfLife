#include "game_of_life_png_exporter.hpp"

void GameOfLifePngExporter::ExportState(
    const std::shared_ptr<Board>& board,
    std::string filepath,
    int cellsize) {

  int width = cellsize * board->GetWidth();
  int height = cellsize * board->GetHeight();

  // Generate the flag
  pngwriter flag{width, height, 0, filepath.data()};
  for (size_t i = 0; i < board->GetHeight(); i++) {
    for (size_t j = 0; j < board->GetWidth(); j++) {
      auto cell = (*board)[{i, j}];

      int positionX = j * cellsize;
      int positionY = i * cellsize;

      if (cell == Cell::kAlive) {
        flag.filledsquare(positionX, positionY, positionX + cellsize - 2,
                          positionY + cellsize - 2, 65535 / 3, 65535 / 2,
                          65535);
      } else {
        flag.filledsquare(positionX, positionY, positionX + cellsize - 2,
                          positionY + cellsize - 2, 65535, 65535 / 2,
                          65535 / 3);
      }
    }
  }

  // Close the flag
  flag.close();
}
