#pragma once

#include <memory>
#include <string>
#include <list>

#include "core/board.hpp"

// Allows making snapshots of an 'Board' object state and restoring it in future.
class BoardMemento {
 private:
  size_t m_max_size;
  // Collection of board's states
  std::list<std::shared_ptr<Board>> m_changes;

 public:
  BoardMemento(int);

  // Adds new element
  void SaveState(const std::shared_ptr<Board>& board);

  // Returns and removes the last inserted element.
  std::shared_ptr<Board> Undo() noexcept(false);
};
