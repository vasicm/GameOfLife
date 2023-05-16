#include "game_of_life_file_exporter.hpp"

GameOfLifeFileExporter::GameOfLifeFileExporter(std::string filename)
    : m_filename(filename) {}

void GameOfLifeFileExporter::ExportState(
    const std::shared_ptr<GameOfLife> &gameOfLife) {
  // Create and open a text file
  std::ofstream outFile(m_filename);

  outFile << gameOfLife->GetCurrentBoardState()->GetWidth() << " "
          << gameOfLife->GetCurrentBoardState()->GetHeight() << std::endl;

  outFile << gameOfLife->GetInitialNumberOfGenerations() << " "
          << gameOfLife->GetTimeIncrementInMs() << std::endl;
  // Write to the file
  outFile << gameOfLife->GetCurrentBoardState()->ToString("1", "0")
          << std::endl;

  // Close the file
  outFile.close();
}
