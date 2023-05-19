#include "board.hpp"

Board::Board(size_t width, size_t height) : width_(width), height_(height) {
  std::vector<std::vector<Cell>> twoDVector(height);
  for (size_t i = 0; i < height; i++) {
    twoDVector[i].resize(width);
  }
  twoDVector_ = twoDVector;
}

bool Board::WrongLocation(int i, int j) const {
  return (i < 0 || i >= height_ || j < 0 || j >= width_) ? true : false;
}
// REVIEW: add copy and move constructor, RULE OF THREE/FIVE
size_t Board::GetWidth() const { return width_; }

size_t Board::GetHeight() const { return height_; }

const Cell& Board::operator[](const Index& index) const noexcept(false) {
  return WrongLocation(index.row, index.col)
             ? throw(std::out_of_range("Wrong"))
             : twoDVector_[index.row][index.col];
}

Cell& Board::operator[](const Index& index) noexcept(false) {
  return WrongLocation(index.row, index.col)
             ? throw(std::out_of_range("Wrong"))
             : twoDVector_[index.row][index.col];
}

std::string Board::ToString(std::string alive, std::string dead) const {
  std::stringstream ss;

  for (auto const& vec : twoDVector_) {
    for (Cell const& cell : vec) {
      ss << (cell == Cell::kDead ? dead : alive);
    }

    ss << std::endl;
  }

  return ss.str();
}
