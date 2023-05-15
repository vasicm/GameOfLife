#pragma once

#pragma once

#include <unistd.h>

#include <filesystem>
#include <iostream>
#include <string>

#include "GameOfLifeLoader.hpp"
#include "GameOfLife.hpp"

using std::filesystem::current_path;

class RandomValuesGameOfLifeLoader : public GameOfLifeLoader {
 private:
  size_t m_boardWidth;
  size_t m_boardheight;
  int m_numberOfGenerations;
  int m_timeIncrementInMs;

 public:
  RandomValuesGameOfLifeLoader(size_t width, size_t height,
                               int numberOfGenerations, int timeIncrementInMs)
      : m_boardWidth(width),
        m_boardheight(height),
        m_numberOfGenerations(numberOfGenerations),
        m_timeIncrementInMs(timeIncrementInMs) {}

  std::shared_ptr<GameOfLife> create() override {
    return std::make_shared<GameOfLife>(createBoard(), m_numberOfGenerations,
                                        m_timeIncrementInMs);
  }

  std::shared_ptr<Board> createBoard() {
    auto board = std::make_shared<Board>(m_boardWidth, m_boardheight);
    // Providing a seed value
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < board->getHeight(); i++) {
      for (size_t j = 0; j < board->getWidth(); j++) {
        (*board)(i, j) = (rand() % 2) == 1;
      }
    }

    return board;
  }
};
