#pragma once
#include <string>

static const std::string ACTIVE_STRING = "x";
static const std::string INACTIVE_STRING = "_";

// enum class Cell {
//     Active,
//     Inactive
// };

class Cell {
 private:
  bool value;

 public:
  Cell() { value = false; }

  Cell(Cell const& c) { value = c.value; }

  bool isActive() { return value; };

  std::string toString(std::string active = "1",
                       std::string inactive = "0") const {
    return value ? active : inactive;
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
