#pragma once

#include "board_memento.hpp"
#include "core/board.hpp"

class GameOfLife {
 private:
  std::shared_ptr<Board> m_currentBoardState;
  int m_currentGeneration = 0;
  int m_initialNumberOfGenerations;
  int m_timeIncrementInMs;
  BoardMemento m_memento;

 public:
  GameOfLife(std::shared_ptr<Board> currentBoardState,
             int nitialNumberOfGenerations, int timeIncrementInMs);
  std::shared_ptr<Board> GetCurrentBoardState() const;
  int GetInitialNumberOfGenerations() const;
  int GetCurrentNumberOfGenerations() const;
  int GetTimeIncrementInMs() const;
  Cell CheckCell(size_t i, size_t j);
  int ActiveNeighborCount(size_t x, size_t y);
  void GoForward();
  void GoBack();
};
