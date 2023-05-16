#include "board_memento.hpp"

void BoardMemento::SaveState(const std::shared_ptr<Board>& board) {
  m_changes.push_back(board);
}

std::shared_ptr<Board> BoardMemento::Undo() {
  auto board = m_changes.back();
  m_changes.pop_back();
  return board;
}
