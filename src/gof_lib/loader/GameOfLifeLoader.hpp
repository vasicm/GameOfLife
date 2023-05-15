#pragma once

#include <unistd.h>

#include <filesystem>
#include <iostream>
#include <string>

#include "GameOfLife.hpp"

using std::filesystem::current_path;

struct GameOfLifeLoader {
  virtual std::shared_ptr<GameOfLife> create() = 0;
};
