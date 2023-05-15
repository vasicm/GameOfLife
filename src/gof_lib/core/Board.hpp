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
  Board(size_t width, size_t height);
  size_t getWidth() const;
  size_t getHeight() const;
  Cell& operator()(size_t row, size_t col);
  inline const Cell& operator()(size_t row, size_t col) const;
  std::string toString(std::string active = "1",
                       std::string inactive = "0") const;
};
