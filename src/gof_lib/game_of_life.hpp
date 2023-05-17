#pragma once

#include "board_memento.hpp"
#include "core/board.hpp"

// Implements the rules of Conway's Game of Life and monitors the status of the game
class GameOfLife {
 private:
  // The current state of the board in the game
  std::shared_ptr<Board> m_currentBoardState;
  // The current generation/iteration of the board.
  int m_currentGeneration = 0;
  // Preserves old states of the board and allows undo operation
  BoardMemento m_memento;

  // Initial number of generations which will be performed on game startup
  int m_initialNumberOfGenerations;

  // Time between generating two iterations during the game simulation
  int m_timeIncrementInMs;

 public:
  GameOfLife(std::shared_ptr<Board> currentBoardState,
             int nitialNumberOfGenerations, int timeIncrementInMs);

  // Returns the current state of the board in the game
  std::shared_ptr<Board> GetCurrentBoardState() const;

  // Retuirns initial number of generations which will be performed on game startup
  int GetInitialNumberOfGenerations() const;

  // Returns the current generation/iteration of the board.
  int GetCurrentNumberOfGenerations() const;

  // Returns time between generating two iterations during the game simulation
  int GetTimeIncrementInMs() const;

  // Returns value for the specified field for the next generation.
  // Or in other words, checks whether the cell should be 'alive' or 'dead' in the next generation.
  Cell CheckCell(size_t i, size_t j);

  // Returns the neighbor number for a specified field
  int ActiveNeighborCount(size_t x, size_t y);

  // Go one generation forward.
  void GoForward();

  // Go one generation back.
  void GoBack();
};
