#pragma once

#include <memory>
#include <string>

#include "game_of_life_loader.hpp"

class GameOfLifeFromFileLoader : public GameOfLifeLoader {
 private:
  std::string m_fileName;

 public:
  GameOfLifeFromFileLoader(std::string fileName);
  std::shared_ptr<GameOfLife> create() override;
};
