#pragma once

#pragma once

#include <unistd.h>

#include <filesystem>
#include <iostream>
#include <string>

#include "game_of_life.hpp"
#include "game_of_life_loader.hpp"

using std::filesystem::current_path;

class RandomValuesGameOfLifeLoader : public GameOfLifeLoader {
 private:
  size_t m_boardWidth;
  size_t m_boardheight;
  int m_numberOfGenerations;
  int m_timeIncrementInMs;

 public:
  RandomValuesGameOfLifeLoader(size_t width, size_t height,
                               int numberOfGenerations, int timeIncrementInMs);
  std::shared_ptr<GameOfLife> create() override;
  std::shared_ptr<Board> createBoard();
};
