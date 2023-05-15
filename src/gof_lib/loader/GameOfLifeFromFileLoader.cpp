#include "GameOfLifeFromFileLoader.hpp"


 GameOfLifeFromFileLoader::GameOfLifeFromFileLoader(std::string fileName) : m_fileName(fileName) {}

  std::shared_ptr<GameOfLife> GameOfLifeFromFileLoader::create() {
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
        (*board)[{i, j}] = (str.at(j) == '1' ? Cell::ALIVE : Cell::DEAD);
      }
    }

    myfile.close();

    return std::make_shared<GameOfLife>(board, genNumber, timeIncrementInMs);
  }
