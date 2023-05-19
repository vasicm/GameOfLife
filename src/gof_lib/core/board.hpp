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
 protected:
  // A structure that allows more intuitive use of the operator [].
  // Example for creating an instance of Index, and using it along with operator[]:
  // Board board{10, 10};
  // board[{i, j}] = Cell::kAlive;
  struct Index {
    size_t row;
    size_t col;
  };
 private:
  // Two-dimensional vector to preserve the value of the field.
  std::vector<std::vector<Cell>> twoDVector_;
  // The width (number of columns) of the board.
  size_t width_;
  // The height (number of rows) of the board.
  size_t height_;

  // Check if the location on board is out of range.
  // Returns 'true' if the location is out of range;
  // Otherwise 'false';
  bool WrongLocation(int, int) const;

 public:
  // A constructor that receives width (number of columns) and height(number of rows)
  // and creates a board with all 'dead' fields.
  Board(size_t width, size_t height);

  // Returns the width, the number of board columns.
  virtual size_t GetWidth() const;

  // Returns the height, the number of board rows.
  virtual size_t GetHeight() const;

  // Overloaded operator [], to access the fields on board.
  virtual const Cell& operator[](const Index&) const noexcept(false);

  // Overloaded operator [], to access the fields on board.
  // Example:
  // Board board{10, 10};
  // board[{i, j}] = Cell::kAlive;
  virtual Cell& operator[](const Index&) noexcept(false);

  // Returns the string representation of the board
  // Input values:
  // alive - the value that the alive fields will have
  // dead - the value that the dead field will have
  std::string ToString(std::string alive = DEFAULT_ALIVE_CELL,
                       std::string dead = DEFAULT_DEAD_CELL) const;
};
