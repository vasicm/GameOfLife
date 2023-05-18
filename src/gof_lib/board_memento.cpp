#include "board_memento.hpp"

BoardMemento::BoardMemento(int max_size) : m_max_size(max_size) {}

void BoardMemento::SaveState(const std::shared_ptr<Board>& board) {
  m_changes.push_back(board);

  if (m_changes.size() > m_max_size)
  {
    m_changes.pop_front();
  }

}

std::shared_ptr<Board> BoardMemento::Undo() {
  if (m_changes.size() == 0)
  {
    throw(std::length_error("Empty!"));
  }

  auto board = m_changes.back();
  m_changes.pop_back();
  return board;
}
