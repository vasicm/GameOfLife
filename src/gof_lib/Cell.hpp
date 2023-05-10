#pragma once
#include <string>

class Cell {
 private:
  bool value;
  const std::string ACTIVE_STRING = "x";
  const std::string INACTIVE_STRING = "_";

 public:
  Cell() { value = false; }

  Cell(Cell const& c) { value = c.value; }

  bool isActive() { return value; };

  std::string toString() const {
    return value ? ACTIVE_STRING : INACTIVE_STRING;
  }

  inline Cell& operator=(const Cell& rhs) {
    if (&rhs == this) return *this;

    value = rhs.value;

    return *this;
  }

  inline Cell& operator=(const bool& rhs) {
    value = rhs;
    return *this;
  }
};