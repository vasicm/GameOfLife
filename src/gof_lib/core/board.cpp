#include "board.hpp"

Board::Board(size_t width, size_t height) : m_width(width), m_height(height) {
  std::vector<std::vector<Cell>> twoDVector(height);
  for (size_t i = 0; i < height; i++) {
    twoDVector[i].resize(width);
  }
  m_twoDVector = twoDVector;
}

bool Board::wrongLocation(int i, int j) const {
  return (i < 0 || i >= m_height || j < 0 || j >= m_width) ? true : false;
}
// REVIEW: add copy and move constructor, RULE OF THREE/FIVE
size_t Board::getWidth() const { return m_width; }

size_t Board::getHeight() const { return m_height; }

const Cell& Board::operator[](const Index& index) const noexcept(false) {
  return wrongLocation(index.row, index.col)
             ? throw(std::out_of_range("Wrong"))
             : m_twoDVector[index.row][index.col];
}

Cell& Board::operator[](const Index& index) noexcept(false) {
  return wrongLocation(index.row, index.col)
             ? throw(std::out_of_range("Wrong"))
             : m_twoDVector[index.row][index.col];
}

std::string Board::toString(std::string alive, std::string dead) const {
  std::stringstream ss;

  for (auto const& vec : m_twoDVector) {
    for (Cell const& cell : vec) {
      ss << (cell == Cell::DEAD ? dead : alive);
    }

    ss << std::endl;
  }

  return ss.str();
}
