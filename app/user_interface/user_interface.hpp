#pragma once

#include <string>

#include "input_option.hpp"
#include "core/board.hpp"

class UserInterface {
 public:
  virtual ~UserInterface(){};
  virtual int GetWidth() = 0;
  virtual int GetHeight() = 0;
  virtual int GetNumberOfGenerations() = 0;
  virtual int GetTimeIncrementInMs() = 0;
  virtual InputOption GetInputOption() = 0;
  virtual std::string GetFileName() = 0;
  virtual void ShowBoard(const std::shared_ptr<Board>& board) = 0;
  virtual void ShowErrorMessage(std::string message) = 0;
};
