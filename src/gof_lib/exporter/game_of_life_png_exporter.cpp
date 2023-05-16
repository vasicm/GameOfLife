#include "game_of_life_png_exporter.hpp"

GameOfLifePngExporter::GameOfLifePngExporter(std::string filepath, int cellsize)
    : m_filepath(filepath), m_cellsize(cellsize) {}

void GameOfLifePngExporter::exportState(
    const std::shared_ptr<GameOfLife>& gof) {
  auto board = gof->getCurrentBoardState();

  int width = m_cellsize * board->getWidth();
  int height = m_cellsize * board->getHeight();

  // Generate the flag
  pngwriter flag{width, height, 0, m_filepath.data()};
  for (size_t i = 0; i < board->getHeight(); i++) {
    for (size_t j = 0; j < board->getWidth(); j++) {
      auto cell = (*board)[{i, j}];

      int positionX = j * m_cellsize;
      int positionY = i * m_cellsize;

      if (cell == Cell::kAlive) {
        flag.filledsquare(positionX, positionY, positionX + m_cellsize - 2,
                          positionY + m_cellsize - 2, 65535 / 3, 65535 / 2,
                          65535);
      } else {
        flag.filledsquare(positionX, positionY, positionX + m_cellsize - 2,
                          positionY + m_cellsize - 2, 65535, 65535 / 2,
                          65535 / 3);
      }
    }
  }

  // Close the flag
  flag.close();
}
