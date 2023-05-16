#pragma once

#include <algorithm>  // std::min
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "cell.hpp"

#define DEFAULT_ALIVE_CELL "1"
#define DEFAULT_DEAD_CELL "0"

class Board {
 private:
  std::vector<std::vector<Cell>> m_twoDVector;
  size_t m_width;
  size_t m_height;

  struct Index {
    size_t row;
    size_t col;
  };
  bool WrongLocation(int, int) const;

 public:
  Board(size_t width, size_t height);
  size_t GetWidth() const;
  size_t GetHeight() const;
  const Cell& operator[](const Index&) const noexcept(false);
  Cell& operator[](const Index&) noexcept(false);
  std::string ToString(std::string alive = DEFAULT_ALIVE_CELL,
                       std::string dead = DEFAULT_DEAD_CELL) const;
};
