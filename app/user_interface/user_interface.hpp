#pragma once

#include <string>

#include "core/board.hpp"
#include "input_option.hpp"

// Interface abstraction to interact with the user.
// The implementation does not depend on the specific input module.
class UserInterface {
 public:
  virtual ~UserInterface(){};

  // Gets the width (number of board columns).
  virtual int GetWidth() = 0;

  // Gets the height (number of board rows).
  virtual int GetHeight() = 0;

  // Retuirns initial number of generations which will be performed on game startup
  virtual int GetNumberOfGenerations() = 0;

  // Returns time between generating two iterations during the game simulation
  virtual int GetTimeIncrementInMs() = 0;

  // Returns the option selected by the user
  virtual InputOption GetInputOption() = 0;

  // Returns the location of a file to export a board, selected by the user
  virtual std::string GetFileName() = 0;

  // Shows the board to the end user
  virtual void ShowBoard(const std::shared_ptr<Board>& board) = 0;

  // Shows an error message to the end user
  virtual void ShowErrorMessage(std::string message) = 0;
};
