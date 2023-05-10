#pragma once
#include <algorithm>  // std::min
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Cell.hpp"

class Board {
 private:
  std::vector<std::vector<Cell>> m_twoDVector;
  size_t m_width;
  size_t m_height;

 public:
  Board(size_t width, size_t height) : m_width(width), m_height(height) {
    std::vector<std::vector<Cell>> twoDVector(height);
    for (size_t i = 0; i < height; i++) {
      twoDVector[i].resize(width);
    }
    m_twoDVector = twoDVector;
  }
  size_t getWidth() const { return m_width; }
  size_t getHeight() const { return m_height; }
  inline Cell& operator()(size_t row, size_t col) {
    return m_twoDVector[row][col];
  }
  inline const Cell& operator()(size_t row, size_t col) const {
    return m_twoDVector[row][col];
  }
  std::string toString() const {
    std::stringstream ss;

    for (auto const& vec : m_twoDVector) {
      for (Cell const& cell : vec) {
        ss << cell.toString();
      }

      ss << std::endl;
    }

    return ss.str();
  }
};
