#include "game_of_life_file_exporter.hpp"
#include <fstream>

void GameOfLifeFileExporter::ExportState(
    const std::shared_ptr<Board> &board,
    int initial_number_of_generations,
    int time_increment_in_ms,
    std::string file_name) {
  // Create and open a text file
  std::ofstream out_file(file_name);

  out_file << board->GetWidth() << " "
          << board->GetHeight() << std::endl;

  out_file << initial_number_of_generations << " "
          << time_increment_in_ms << std::endl;
  // Write to the file
  out_file << board->ToString("1", "0")
          << std::endl;

  // Close the file
  out_file.close();
}

bool GameOfLifeFileExporter::CheckIfFileExists(std::string file_name) {
  std::ifstream file;
  bool file_exists = false;
  file.open(file_name);
  if(file.is_open()) {
    file_exists = true;
    file.close();
  }

  return file_exists;
}
