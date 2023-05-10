#pragma once

#include "GameOfLife.hpp"


#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>

using std::filesystem::current_path;

struct GameOfLifeLoader {
  virtual std::shared_ptr<GameOfLife> create() = 0;
};

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

class GameOfLifeFromFileLoader : public GameOfLifeLoader {
 private:
  std::string m_fileName;

 public:
  GameOfLifeFromFileLoader(std::string fileName) : m_fileName(fileName) {}

  std::shared_ptr<GameOfLife> create() override {
    std::ifstream myfile;
    myfile.open(m_fileName);
    size_t width = 0;
    myfile >> width;
    size_t height = 0;
    myfile >> height;
    int genNumber = 0;
    myfile >> genNumber;
    int timeIncrementInMs = 0;
    myfile >> timeIncrementInMs;

    auto board = std::make_shared<Board>(width, height);
    for (size_t i = 0; i < board->getHeight(); i++) {
      std::string str;
      myfile >> str;
      for (size_t j = 0; j < board->getWidth(); j++) {
        (*board)(i, j) = str.at(j) == '0' ? false : true;
      }
    }

    myfile.close();

    return std::make_shared<GameOfLife>(board, genNumber, timeIncrementInMs);
  }
};
