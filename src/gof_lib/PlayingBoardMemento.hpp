#pragma once

#include <memory>
#include <string>
#include <vector>

#include "core/Board.hpp"

class PlayingBoardMemento {
 private:
  std::vector<std::shared_ptr<Board>> m_changes;

 public:
  void saveState(const std::shared_ptr<Board>& board) {
    m_changes.push_back(board);
  }

  std::shared_ptr<Board> undo() {
    auto board = m_changes.back();
    m_changes.pop_back();
    return board;
  }
};
