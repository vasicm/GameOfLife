#pragma once

#include "board_memento.hpp"
#include "core/board.hpp"

#define DEFAULT_HISTORY_SIZE 20

// Implements the rules of Conway's Game of Life and monitors the status of the game
class GameOfLife {
 private:
  // The current state of the board in the game
  std::shared_ptr<Board> current_board_state_;
  // The current generation/iteration of the board.
  int current_generation_ = 0;
  // Preserves old states of the board and allows undo operation
  BoardMemento memento_;

  // Initial number of generations which will be performed on game startup
  int initial_number_of_generations_;

  // Time between generating two iterations during the game simulation
  int time_increment_in_ms_;

 public:
  GameOfLife(std::shared_ptr<Board> current_board_state,
             int nitial_number_of_generations, int time_increment_in_ms,
             int history_size = DEFAULT_HISTORY_SIZE);

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
  void GoBack() noexcept(false);
};
