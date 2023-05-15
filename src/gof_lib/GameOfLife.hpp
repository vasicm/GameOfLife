#pragma once

#include "core/Board.hpp"
#include "BoardMemento.hpp"

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
  std::shared_ptr<Board> getCurrentBoardState() const;
  int getInitialNumberOfGenerations() const;
  int getCurrentNumberOfGenerations() const;
  int getTimeIncrementInMs() const;
  bool CheckCell(int i, int j);
  int ActiveNeighborCount(int x, int y);
  void goForward();
  void goBack();
};
