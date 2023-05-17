#pragma once

#include <memory>
#include <string>
#include <vector>

#include "core/board.hpp"

// Allows making snapshots of an 'Board' object state and restoring it in future.
class BoardMemento {
 private:
  // TODO: consider using stack or list. Can be discussed.

  // Collection of board's states
  std::vector<std::shared_ptr<Board>> m_changes;

 public:

  // Adds new element
  void SaveState(const std::shared_ptr<Board>& board);

  // Returns and removes the last inserted element.
  std::shared_ptr<Board> Undo();
};
