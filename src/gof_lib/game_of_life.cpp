#include "game_of_life.hpp"

#include "board_memento.hpp"

GameOfLife::GameOfLife(std::shared_ptr<Board> current_board_state,
                       int nitial_number_of_generations, int time_increment_in_ms,
                       int history_size)
    : current_board_state_(current_board_state),
      initial_number_of_generations_(nitial_number_of_generations),
      time_increment_in_ms_(time_increment_in_ms),
      memento_(history_size) {}

std::shared_ptr<Board> GameOfLife::GetCurrentBoardState() const {
  return current_board_state_;
}

int GameOfLife::GetInitialNumberOfGenerations() const {
  return initial_number_of_generations_;
}

int GameOfLife::GetCurrentNumberOfGenerations() const {
  return current_generation_;
}

int GameOfLife::GetTimeIncrementInMs() const { return time_increment_in_ms_; }

Cell GameOfLife::CheckCell(size_t i, size_t j) {
  auto active_neighbor_count = this->ActiveNeighborCount(i, j);
  bool is_old_cell_alive = (*current_board_state_)[{i, j}] == Cell::kAlive;
  bool is_cell_alive = (active_neighbor_count == 3 ||
                      (is_old_cell_alive && active_neighbor_count == 2));
  return is_cell_alive ? Cell::kAlive : Cell::kDead;
}

int GameOfLife::ActiveNeighborCount(size_t x, size_t y) {
  size_t x_max = current_board_state_->GetHeight() - 1;
  size_t y_max = current_board_state_->GetWidth() - 1;

  size_t x_start = x == 0 ? 0 : x - 1;
  size_t x_end = std::min(x + 1, x_max);
  size_t y_start = y == 0 ? 0 : y - 1;
  size_t y_end = std::min(y + 1, y_max);

  int count = 0;
  for (size_t i = x_start; i <= x_end; i++) {
    for (size_t j = y_start; j <= y_end; j++) {
      if ((*current_board_state_)[{i, j}] == Cell::kAlive &&
          (i != x || j != y)) {
        count++;
      }
    }
  }

  return count;
}

void GameOfLife::GoForward() {
  size_t height = current_board_state_->GetHeight();
  size_t width = current_board_state_->GetWidth();

  auto new_board = std::make_shared<Board>(width, height);

  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      (*new_board)[{i, j}] = CheckCell(i, j);
    }
  }

  memento_.SaveState(current_board_state_);

  current_generation_++;
  current_board_state_ = new_board;
}

void GameOfLife::GoBack() {
  current_board_state_ = memento_.Undo();
  current_generation_--;
}
