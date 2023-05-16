#pragma once

#include <pngwriter.h>

#include <string>

#include "game_of_life.hpp"

class GameOfLifePngExporter {
 private:
  std::string m_filepath;
  int m_cellsize;

 public:
  GameOfLifePngExporter(std::string filepath, int cellsize);
  void ExportState(const std::shared_ptr<GameOfLife>& gof);
};
