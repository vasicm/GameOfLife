#include "GameOfLife.hpp"

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

bool GameOfLife::CheckCell(int i, int j) {
  auto activeNeighborCount = this->ActiveNeighborCount(i, j);
  bool isCellLive = (*m_currentBoardState)(i, j).isActive();
  return activeNeighborCount == 3 || (isCellLive && activeNeighborCount == 2);
}

int GameOfLife::ActiveNeighborCount(int x, int y) {
  // TODO: check types
  int xMax = m_currentBoardState->getHeight() - 1;

  if (xMax <= 1) {
    return 0;
  }

  int yMax = m_currentBoardState->getWidth() - 1;

  auto xStart = std::max(x - 1, 0);
  auto xEnd = std::min(x + 1, xMax);
  auto yStart = std::max(y - 1, 0);
  auto yEnd = std::min(y + 1, yMax);

  int count = 0;
  for (int i = xStart; i <= xEnd; i++) {
    for (int j = yStart; j <= yEnd; j++) {
      if ((*m_currentBoardState)(i, j).isActive() && (i != x || j != y)) {
        count++;
      }
    }
  }

  return count;
}

void GameOfLife::goForward() {
  int height = m_currentBoardState->getHeight();
  int width = m_currentBoardState->getWidth();

  auto newBoard = std::make_shared<Board>(width, height);

  // Providing a seed value
  srand((unsigned)time(NULL));
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      (*newBoard)(i, j) = CheckCell(i, j);
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
