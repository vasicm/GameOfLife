#pragma once

#include <memory>
#include <string>
#include <regex>

#include "game_of_life_loader.hpp"

class GameOfLifeFromFileLoader : public GameOfLifeLoader {
 private:
  std::string m_fileName;
  void ValidateIfFileReachedEnd(std::ifstream& myfile);
  std::istringstream GetLineAsStream(std::ifstream& myfile, const std::regex& regex) noexcept(false);
  std::regex GetRegexForBoardLine(size_t width);
 public:
  GameOfLifeFromFileLoader(std::string fileName);
  std::shared_ptr<GameOfLife> Create() override;
};
