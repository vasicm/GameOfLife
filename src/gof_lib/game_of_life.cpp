#include "game_of_life.hpp"

#include "board_memento.hpp"
#include "performance_measurer.hpp"

#include <future>

GameOfLife::GameOfLife(std::shared_ptr<Board> currentBoardState,
                       int nitialNumberOfGenerations, int timeIncrementInMs,
                       int historySize)
    : m_currentBoardState(currentBoardState),
      m_initialNumberOfGenerations(nitialNumberOfGenerations),
      m_timeIncrementInMs(timeIncrementInMs),
      m_memento(historySize) {}

std::shared_ptr<Board> GameOfLife::GetCurrentBoardState() const {
  return m_currentBoardState;
}

int GameOfLife::GetInitialNumberOfGenerations() const {
  return m_initialNumberOfGenerations;
}

int GameOfLife::GetCurrentNumberOfGenerations() const {
  return m_currentGeneration;
}

int GameOfLife::GetTimeIncrementInMs() const { return m_timeIncrementInMs; }

Cell GameOfLife::CheckCell(size_t i, size_t j) {
  auto activeNeighborCount = this->ActiveNeighborCount(i, j);
  bool isOldCellAlive = (*m_currentBoardState)[{i, j}] == Cell::kAlive;
  bool isCellAlive = (activeNeighborCount == 3 ||
                      (isOldCellAlive && activeNeighborCount == 2));
  return isCellAlive ? Cell::kAlive : Cell::kDead;
}

int GameOfLife::ActiveNeighborCount(size_t x, size_t y) {
  // TODO: check types
  size_t xMax = m_currentBoardState->GetHeight() - 1;
  size_t yMax = m_currentBoardState->GetWidth() - 1;

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

void GameOfLife::FillBoard(std::shared_ptr<Board> newBoard, size_t start_from, size_t increment) {
  auto width =  newBoard->GetWidth();

  auto count = newBoard->GetHeight() * newBoard->GetWidth();

  for (size_t k = start_from; k < count; k+=increment)
  {
    size_t i = k / width;
    size_t j = k % width;
    (*newBoard)[{i, j}] = CheckCell(i, j);
  }

//   for (size_t i = 0; i < newBoard->GetHeight(); i++) {
//     for (size_t j = 0; j < newBoard->GetWidth(); j++) {
//       (*newBoard)[{i, j}] = CheckCell(i, j);
//     }
//   }
}

void GameOfLife::GoForward() {

  size_t height = m_currentBoardState->GetHeight();
  size_t width = m_currentBoardState->GetWidth();

  auto newBoard = std::make_shared<Board>(width, height);

  PerformanceMeasurer::StarMeasuring(0);
  auto f = std::async(&GameOfLife::FillBoard, this, newBoard, 0, 1);

  f.get();
  std::cout << "Elapsed time, one async thread:" << PerformanceMeasurer::GetElapsedTime(0)<< std::endl;

  //f2.get();

  PerformanceMeasurer::StarMeasuring(1);
  auto f1 = std::async(&GameOfLife::FillBoard, this, newBoard, 0, 2);
  auto f2 = std::async(&GameOfLife::FillBoard, this, newBoard, 1, 2);
  f1.get();
  f2.get();
  std::cout << "Elapsed time, two async thread:" << PerformanceMeasurer::GetElapsedTime(1)<< std::endl;

  PerformanceMeasurer::StarMeasuring(2);
  FillBoard(newBoard, 0, 1);
  std::cout << "Elapsed time, main thread:" << PerformanceMeasurer::GetElapsedTime(2)<< std::endl;
//   for (size_t i = 0; i < height; i++) {
//     for (size_t j = 0; j < width; j++) {
//       (*newBoard)[{i, j}] = CheckCell(i, j);
//     }
//   }

  m_memento.SaveState(m_currentBoardState);

  m_currentGeneration++;
  m_currentBoardState = newBoard;


}

void GameOfLife::GoBack() {
  m_currentBoardState = m_memento.Undo();
  m_currentGeneration--;
}
