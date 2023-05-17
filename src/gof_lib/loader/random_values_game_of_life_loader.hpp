#pragma once

#pragma once

#include <unistd.h>

#include <filesystem>
#include <iostream>
#include <string>

#include "game_of_life.hpp"
#include "game_of_life_loader.hpp"

using std::filesystem::current_path;

// A specific implementation of abstract class 'GameOfLifeLoader'.
// Allows loading/creating a 'GameOfLife' instance based on input parameters with randomly populated fields.
class RandomValuesGameOfLifeLoader : public GameOfLifeLoader {
 private:
  // The width (number of columns) of the board.
  size_t m_boardWidth;
  // The height (number of rows) of the board.
  size_t m_boardheight;
  // Initial number of generations which will be performed on game startup
  int m_numberOfGenerations;
  // Time between generating two iterations during the game simulation
  int m_timeIncrementInMs;

  // Creates board with randomly populated fields
  std::shared_ptr<Board> createBoard();
 public:
  RandomValuesGameOfLifeLoader(size_t width, size_t height,
                               int numberOfGenerations, int timeIncrementInMs);

  // Creates 'GameOfLife' instance with 'Board; instance with randomly populated fields
  std::shared_ptr<GameOfLife> Create() override;

};
