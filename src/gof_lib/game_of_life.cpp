#include "game_of_life.hpp"

#include "board_memento.hpp"

GameOfLife::GameOfLife(std::shared_ptr<Board> currentBoardState,
                       int nitialNumberOfGenerations, int timeIncrementInMs)
    : m_currentBoardState(currentBoardState),
      m_initialNumberOfGenerations(nitialNumberOfGenerations),
      m_timeIncrementInMs(timeIncrementInMs) {}

std::shared_ptr<Board> GameOfLife::getCurrentBoardState() const {
  return m_currentBoardState;
}

int GameOfLife::getInitialNumberOfGenerations() const {
  return m_initialNumberOfGenerations;
}

int GameOfLife::getCurrentNumberOfGenerations() const {
  return m_currentGeneration;
}

int GameOfLife::getTimeIncrementInMs() const { return m_timeIncrementInMs; }

Cell GameOfLife::CheckCell(size_t i, size_t j) {
  auto activeNeighborCount = this->ActiveNeighborCount(i, j);
  bool isOldCellAlive = (*m_currentBoardState)[{i, j}] == Cell::kAlive;
  bool isCellAlive = (activeNeighborCount == 3 ||
                      (isOldCellAlive && activeNeighborCount == 2));
  return isCellAlive ? Cell::kAlive : Cell::kDead;
}

int GameOfLife::ActiveNeighborCount(size_t x, size_t y) {
  // TODO: check types
  size_t xMax = m_currentBoardState->getHeight() - 1;
  size_t yMax = m_currentBoardState->getWidth() - 1;

  size_t xStart = x == 0 ? 0 : x - 1;
  size_t xEnd = std::min(x + 1, xMax);
  size_t yStart = y == 0 ? 0 : y - 1;
  size_t yEnd = std::min(y + 1, yMax);

  int count = 0;
  for (size_t i = xStart; i <= xEnd; i++) {
    for (size_t j = yStart; j <= yEnd; j++) {
      if ((*m_currentBoardState)[{i, j}] == Cell::kAlive &&
          (i != x || j != y)) {
        count++;
      }
    }
  }

  return count;
}

void GameOfLife::goForward() {
  size_t height = m_currentBoardState->getHeight();
  size_t width = m_currentBoardState->getWidth();

  auto newBoard = std::make_shared<Board>(width, height);

  // Providing a seed value
  srand((unsigned)time(NULL));
  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      (*newBoard)[{i, j}] = CheckCell(i, j);
    }
  }

  m_memento.saveState(m_currentBoardState);

  m_currentGeneration++;
  m_currentBoardState = newBoard;
}

void GameOfLife::goBack() {
  if (m_currentGeneration) {
    m_currentBoardState = m_memento.undo();
    m_currentGeneration--;
  }
}
