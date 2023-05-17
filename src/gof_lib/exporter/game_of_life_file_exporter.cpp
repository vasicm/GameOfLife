#include "game_of_life_file_exporter.hpp"

void GameOfLifeFileExporter::ExportState(
    const std::shared_ptr<Board> &board,
    int initial_number_of_generations,
    int time_increment_in_ms,
    std::string filename) {
  // Create and open a text file
  std::ofstream outFile(filename);

  outFile << board->GetWidth() << " "
          << board->GetHeight() << std::endl;

  outFile << initial_number_of_generations << " "
          << time_increment_in_ms << std::endl;
  // Write to the file
  outFile << board->ToString("1", "0")
          << std::endl;

  // Close the file
  outFile.close();
}
