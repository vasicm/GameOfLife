#pragma once

#include <memory>
#include <string>
#include <vector>

#include "core/board.hpp"

class BoardMemento {
 private:
  // REVIEW: consider using stack
  std::vector<std::shared_ptr<Board>> m_changes;

 public:
  void saveState(const std::shared_ptr<Board>& board);
  std::shared_ptr<Board> undo();
};
