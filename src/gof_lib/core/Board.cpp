#include "Board.hpp"

Board::Board(size_t width, size_t height) : m_width(width), m_height(height) {
  std::vector<std::vector<Cell>> twoDVector(height);
  for (size_t i = 0; i < height; i++) {
    twoDVector[i].resize(width);
  }
  m_twoDVector = twoDVector;
}

size_t Board::getWidth() const { return m_width; }

size_t Board::getHeight() const { return m_height; }

Cell& Board::operator()(size_t row, size_t col) {
  return m_twoDVector[row][col];
}

inline const Cell& Board::operator()(size_t row, size_t col) const {
  return m_twoDVector[row][col];
}

std::string Board::toString(std::string active, std::string inactive) const {
  std::stringstream ss;

  for (auto const& vec : m_twoDVector) {
    for (Cell const& cell : vec) {
      ss << cell.toString(active, inactive);
    }

    ss << std::endl;
  }

  return ss.str();
}
