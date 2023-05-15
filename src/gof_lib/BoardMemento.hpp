#pragma once

#include <memory>
#include <string>
#include <vector>

#include "core/Board.hpp"

class BoardMemento {
 private:
  std::vector<std::shared_ptr<Board>> m_changes;

 public:
  void saveState(const std::shared_ptr<Board>& board);
  std::shared_ptr<Board> undo();
};
