#pragma once

#include <string>

#include "game_of_life.hpp"

class GameOfLifeFileExporter {
 private:
  std::string m_filename;

 public:
  GameOfLifeFileExporter(std::string filename);
  void exportState(const std::shared_ptr<GameOfLife> &gameOfLife);
};
