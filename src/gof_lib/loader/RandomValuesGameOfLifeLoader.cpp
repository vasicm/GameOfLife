#include "RandomValuesGameOfLifeLoader.hpp"

  RandomValuesGameOfLifeLoader::RandomValuesGameOfLifeLoader(size_t width, size_t height,
                               int numberOfGenerations, int timeIncrementInMs)
      : m_boardWidth(width),
        m_boardheight(height),
        m_numberOfGenerations(numberOfGenerations),
        m_timeIncrementInMs(timeIncrementInMs) {}

  std::shared_ptr<GameOfLife> RandomValuesGameOfLifeLoader::create() {
    return std::make_shared<GameOfLife>(createBoard(), m_numberOfGenerations,
                                        m_timeIncrementInMs);
  }

  std::shared_ptr<Board> RandomValuesGameOfLifeLoader::createBoard() {
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
