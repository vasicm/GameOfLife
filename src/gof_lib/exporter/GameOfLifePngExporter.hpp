#pragma once

#include <pngwriter.h>

#include <string>

#include "GameOfLife.hpp"

class GameOfLifePngExporter {
 private:
  std::string m_filepath;
  int m_cellsize;

 public:
  GameOfLifePngExporter(std::string filepath, int cellsize);
  void exportState(const std::shared_ptr<GameOfLife>& gof);
};
