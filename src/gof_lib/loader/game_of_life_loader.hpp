#pragma once

#include <unistd.h>

#include <filesystem>
#include <iostream>
#include <string>

#include "game_of_life.hpp"

using std::filesystem::current_path;

struct GameOfLifeLoader {
  virtual std::shared_ptr<GameOfLife> Create() = 0;
};
