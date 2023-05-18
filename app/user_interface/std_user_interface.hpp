#pragma once

#include <iostream>

#include "user_interface.hpp"

class StdUserInterface : public UserInterface {
 private:
  void DisplayMainMenu();

  // Reads empty string.
  // After reading the value, the following input will be an empty string.
  // Without this logic, the following method that reads the value from the input
  // can mistakenly read the empty string.
  void CleanInput();

 public:
  int GetWidth();
  int GetHeight();
  int GetNumberOfGenerations();
  int GetTimeIncrementInMs();
  InputOption GetInputOption();
  std::string GetFileName();
  void ShowBoard(const std::shared_ptr<Board>& board, int generation);
  void ShowErrorMessage(std::string message);
};
