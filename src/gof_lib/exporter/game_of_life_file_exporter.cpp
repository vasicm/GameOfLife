#include "game_of_life_file_exporter.hpp"

GameOfLifeFileExporter::GameOfLifeFileExporter(std::string filename)
    : m_filename(filename) {}

void GameOfLifeFileExporter::exportState(
    const std::shared_ptr<GameOfLife> &gameOfLife) {
  // Create and open a text file
  std::ofstream outFile(m_filename);

  outFile << gameOfLife->getCurrentBoardState()->getWidth() << " "
          << gameOfLife->getCurrentBoardState()->getHeight() << std::endl;

  outFile << gameOfLife->getInitialNumberOfGenerations() << " "
          << gameOfLife->getTimeIncrementInMs() << std::endl;
  // Write to the file
  outFile << gameOfLife->getCurrentBoardState()->toString("1", "0")
          << std::endl;

  // Close the file
  outFile.close();
}
