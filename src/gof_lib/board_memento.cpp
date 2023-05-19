#include "board_memento.hpp"

BoardMemento::BoardMemento(int max_size) : max_size_(max_size) {}

void BoardMemento::SaveState(const std::shared_ptr<Board>& board) {
  board_collection_.push_back(board);

  if (board_collection_.size() > max_size_)
  {
    board_collection_.pop_front();
  }

}

std::shared_ptr<Board> BoardMemento::Undo() {
  if (board_collection_.size() == 0)
  {
    throw(std::length_error("Empty!"));
  }

  auto board = board_collection_.back();
  board_collection_.pop_back();
  return board;
}
