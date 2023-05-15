#include "BoardMemento.hpp"

  void BoardMemento::saveState(const std::shared_ptr<Board>& board) {
    m_changes.push_back(board);
  }

  std::shared_ptr<Board> BoardMemento::undo() {
    auto board = m_changes.back();
    m_changes.pop_back();
    return board;
  }
