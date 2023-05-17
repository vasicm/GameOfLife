#pragma once

#include <unistd.h>

#include <filesystem>
#include <iostream>
#include <string>

#include "game_of_life.hpp"

using std::filesystem::current_path;

// An abstract class that provides a method for creating 'GameOfLife' instance.
// The idea is to use the class to access a specific loader through reference/pointer to this class.
struct GameOfLifeLoader {
  virtual std::shared_ptr<GameOfLife> Create() = 0;
};
