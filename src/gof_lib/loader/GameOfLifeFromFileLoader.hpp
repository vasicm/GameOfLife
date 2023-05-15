#pragma once

#include <string>
#include <memory>

#include "GameOfLifeLoader.hpp"

class GameOfLifeFromFileLoader : public GameOfLifeLoader {
 private:
  std::string m_fileName;

 public:
  GameOfLifeFromFileLoader(std::string fileName);
  std::shared_ptr<GameOfLife> create() override;
};
