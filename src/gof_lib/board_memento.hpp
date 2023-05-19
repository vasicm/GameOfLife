#pragma once

#include <memory>
#include <string>
#include <list>

#include "core/board.hpp"

// Allows making snapshots of an 'Board' object state and restoring it in future.
class BoardMemento {
 private:
  // Maximum number of copies that memento can hold
  size_t max_size_;
  // Collection of board's states
  std::list<std::shared_ptr<Board>> board_collection_;

 public:
  BoardMemento(int);

  // Adds a new element to the collection.
  // If the collection is full, i.e. exceeds the maximum number of elements,
  // the oldest copy will be deleted.
  void SaveState(const std::shared_ptr<Board>& board);

  // Returns and removes the last inserted/newest element.
  std::shared_ptr<Board> Undo() noexcept(false);
};
